#include "ev3api.h"
#include "hal_ev3_std.h"

#include "ScenarioConductor_ohs.h"

extern FILE* gBtHandle;//デバッグ用

/**
 * コンストラクタ
 */
ScenarioConductor_ohs::ScenarioConductor_ohs( EvStateAdmin_ohs* ev_state_admin, LineTracer_ohs* line_tracer, PatternSequencer_ohs* pettern_sequencer, TrackCompass_ohs* track_compass )
:mEvStateAdmin( ev_state_admin ),
 mLineTracer( line_tracer ),
 mPatternSequencer( pettern_sequencer ),
 mTrackCompass( track_compass )
{
	memset( mScenario, 0, sizeof(mScenario));
	//初期待機状態の入力
	mScenario[INIT_SCENARIO_ID].move_event = EX_SLIP;
	mScenario[INIT_SCENARIO_ID].pattern_id = 0;
	mScenario[INIT_SCENARIO_ID].next_scene = INIT_SCENARIO_ID;
	mScenario[INIT_SCENARIO_ID].event_value = 0;

	//実行シナリオID = 初期待機状態
	mScenarioID = INIT_SCENARIO_ID;

	//状態確認インデックスのメソッド登録
	mCheckMethod[CLS_BLK] = &ScenarioConductor_ohs::checkRayRef;
	mCheckMethod[CLS_GRY] = &ScenarioConductor_ohs::checkRayRef;
	mCheckMethod[CLS_WHT] = &ScenarioConductor_ohs::checkRayRef;
	mCheckMethod[RUN_MLG] = &ScenarioConductor_ohs::checkMileage;
	mCheckMethod[EV3_DEG] = &ScenarioConductor_ohs::checkAngle;
	mCheckMethod[TIL_DEG] = &ScenarioConductor_ohs::checkTailDeg;
	mCheckMethod[GYR__ST] = &ScenarioConductor_ohs::checkGyro;
	mCheckMethod[GYR_UST] = &ScenarioConductor_ohs::checkGyro;
	mCheckMethod[EX_SLIP] = &ScenarioConductor_ohs::checkSlip;
	mCheckMethod[EX_END]  = &ScenarioConductor_ohs::checkQuit;
	mCheckMethod[CLS_LIN] = &ScenarioConductor_ohs::checkRayRef;//20160913追加
	mCheckMethod[EX_JUMP] = &ScenarioConductor_ohs::checkJump;//20160915追加
	mCheckMethod[RAXIS_T] = &ScenarioConductor_ohs::checkRAxisTurn;//20160915追加
}

/**
 * デストラクタ
 */
ScenarioConductor_ohs::~ScenarioConductor_ohs() {
}

/**
 * シナリオ実行
 */
BOOL ScenarioConductor_ohs::execScenario() {
	BOOL nextEventF = false;
	UCHR ucMoveEvent = mScenario[mScenarioID].move_event;

	/* インデックスチェック ------------------------------------------- */
	//実行インデックス
	if( mScenarioID >= SCENARIO_MAX_NUM ) {
		quitCommand();
		return false;
	}
	//達成条件ID
	if( ucMoveEvent >= EVENT_NUM ) {
		quitCommand();
		return false;
	}

	//転倒検知シナリオ終了
#ifdef FALLING_STOP
	if( mEvStateAdmin->getBalanceState() == GSTA_FALLING ) { quitCommand(); }
#endif

	/* シナリオ実行 ------------------------------------------- */
	if( mScenario[mScenarioID].pattern_id < PATTERN_NUM  ) {
		//ライントレーサに終了通知を渡す
		mLineTracer->postLineTraceStop();
		//パターンシーケンス指示
		mPatternSequencer->callPatternRunning( mScenario[mScenarioID].pattern_id );
	} else {
		switch( mScenario[mScenarioID].pattern_id ) {
			case LINETRACER_NORMAL:					//ライントレース指示＠通常
				mLineTracer->postLineTraceConduct( false );
				break;
			case LINETRACER_SPEED:					//ライントレース指示＠高速
				mLineTracer->postLineTraceConduct( true );
				break;
			case TRACKCOMPASS_CHECK:				//方位想定回転＠原位置セット
				mTrackCompass->setReferenceAxis();
				break;
			case TRACKCOMPASS_TRUN:					//方位想定回転＠回転
				mLineTracer->postLineTraceStop();//ライントレーサに終了通知を渡す
				mTrackCompass->callRAxisTurn(( int32_t )( mScenario[mScenarioID].event_value ));
				break;
			case TRACKCOMPASS_MOVEB:					//方位想定前後進＠倒立
				mLineTracer->postLineTraceStop();//ライントレーサに終了通知を渡す
				mTrackCompass->callRAxisMove(( int32_t )( mScenario[mScenarioID].event_value ), true );
				break;
			case TRACKCOMPASS_MOVE:					//方位想定前後進＠支え有り
				mLineTracer->postLineTraceStop();//ライントレーサに終了通知を渡す
				mTrackCompass->callRAxisMove(( int32_t )( mScenario[mScenarioID].event_value ), false );
				break;
			default:
				break;
		}
	}

	/* シナリオ達成チェック ------------------------------------------- */
	//本体状態管理を更新
	if( mEvStateAdmin->setStateCollection() == false ) {
		return true;//状態変化無し
	}

	//達成確認
	nextEventF = ( this->*mCheckMethod[ucMoveEvent] )();//登録されたメソッドの使用

	//達成フラグのチェック
	if( nextEventF == true ) { 
#ifdef TRANSITION_SOUND
        ev3_speaker_play_tone( NOTE_B6, 80 );

        fprintf( gBtHandle,"ID      [%d]\r\n",(int)getID());
        fprintf( gBtHandle,"Mileage [%d]\r\n",(int)mEvStateAdmin->getMileage());
        fprintf( gBtHandle,"Angle   [%d]\r\n",(int)mEvStateAdmin->getBodyAngle());
#endif
		//シナリオ更新(異常値返却ならば終了)
		if( setScenarioUpDate() == false ) { return false; }
	}

	//正常終了
	return true;
}

/* 光学センサの状態を確認 */
bool ScenarioConductor_ohs::checkRayRef() {
	SENC_CLR getSencClr = mEvStateAdmin->getColorSensorState();

	switch( mScenario[mScenarioID].move_event ) {
		case CLS_BLK:
			if( getSencClr == SCLR_BLACK ) { return true; }
			break;
		case CLS_GRY:
			if( getSencClr == SCLR_GRAY ) { return true; }
			break;
		case CLS_WHT:
			if( getSencClr == SCLR_WHITE ) { return true; }
			break;
		case CLS_LIN:
			if( getSencClr != SCLR_WHITE ) { return true; }
			break;
		default:
			break;
	}

	return false;
}

/* 走行距離を確認 */
bool ScenarioConductor_ohs::checkMileage() {
	SLNG lGetNowMlg = ( SLNG )mEvStateAdmin->getMileage();
	SLNG lTargetMlg = mScenario[mScenarioID].event_value;

	if( lTargetMlg > 0 ) {
		//前進チェック
		if( lGetNowMlg > lTargetMlg ) { return true; }
	} else {
		//後進チェック
		if( lGetNowMlg < lTargetMlg ) { return true; }
	}
	return false;
}

/* 走行体角度を確認 */
bool ScenarioConductor_ohs::checkAngle() {
	SLNG lGetNowDeg = ( SLNG )mEvStateAdmin->getBodyAngle();
	SLNG lTargetDeg = mScenario[mScenarioID].event_value;

	if( lTargetDeg > 0 ) {
		//cwチェック
		if( lGetNowDeg > lTargetDeg ) { return true; }
	} else {
		//ccwチェック
		if( lGetNowDeg < lTargetDeg ) { return true; }
	}
	return false;
}

/* 尻尾角度を確認 */
bool ScenarioConductor_ohs::checkTailDeg() {
	SLNG lGetNowDeg = ( SLNG )mEvStateAdmin->getTailAngle();
	SLNG lTrgDegMax = 0;
	SLNG lTrgDegMin = 0;

	//目標達成範囲の設定
	lTrgDegMax = mScenario[mScenarioID].event_value + TIL_DEG_PERMISSION; 
	lTrgDegMin = mScenario[mScenarioID].event_value - TIL_DEG_PERMISSION;

	if(( lTrgDegMax > lGetNowDeg ) && ( lGetNowDeg > lTrgDegMin )) {
		return true;
	}
	return false;
}

/* ジャイロ状態を確認 */
bool ScenarioConductor_ohs::checkGyro() {
	GYRO_STATE getGyroState = mEvStateAdmin->getBalanceState();
	switch( mScenario[mScenarioID].move_event ) {
		case GYR__ST:
			if( getGyroState == GSTA_STABILITY ) { return true; }
			break;
		case GYR_UST:
			if( getGyroState == GSTA_UNSTABLE ) { return true; }
			break;
		default:
			break;
	}
	
	return false;
}

/* シナリオ終了操作 */
bool ScenarioConductor_ohs::checkQuit() {
	//終了操作
	quitCommand();
	return true;
}

/* シナリオ現状を保持する（外部入力待ち） */
bool ScenarioConductor_ohs::checkSlip() {
	return false;
}

/* シナリオ強制移行操作 */
bool ScenarioConductor_ohs::checkJump() {
	return true;
}

/* 方位指定回転達成確認 */
bool ScenarioConductor_ohs::checkRAxisTurn() {
	return ( bool )mTrackCompass->getRAxisTurnFinish( mScenario[mScenarioID].event_value );
}

// ../workspace/EV3_HAL2016/main_app/ScenarioConductor_ohs.cpp:33:24: error: cannot convert 'ScenarioConductor_ohs::checkSlip' from type 'bool (ScenarioConductor_ohs::)(int)' to type 'bool (ScenarioConductor_ohs::*)()'


/**
 * シナリオセット
 */
BOOL ScenarioConductor_ohs::setScenario( UCHR uc_scen_no ) {
	//指定インデックスが範囲内
	if( uc_scen_no < SCENARIO_MAX_NUM ) {
		mScenarioID = uc_scen_no;

		//本体状態管理のリフレッシュ
		mEvStateAdmin->setStateRefresh();

		return true;
	}
	return false;
}

/**
 * 指揮終了
 */
void ScenarioConductor_ohs::quitCommand() {
	//シナリオインデックスを範囲外にする = 終了
	mScenarioID = SCENARIO_MAX_NUM;
	//ライントレーサに終了通知を渡す
	mLineTracer->postLineTraceStop();
	//パターンシーケンサに終了通知を渡す
	mPatternSequencer->callSequencStop();
}

/**
 * シナリオ更新
 */
BOOL ScenarioConductor_ohs::setScenarioUpDate() {
	//インデックスチェック
	if( mScenarioID >= SCENARIO_MAX_NUM ) { return false; }

	//本体状態管理のリフレッシュ
	mEvStateAdmin->setStateRefresh();

	//次のシナリオへ
	mScenarioID = mScenario[mScenarioID].next_scene;

	//シナリオ範囲オーバチェック
	if( mScenarioID >= SCENARIO_MAX_NUM ) {
		//終了操作
		quitCommand();
		//異常終了
		return false;
	}

	return true;
}

/**
 * シナリオインデックスの外部登録
 */
BOOL ScenarioConductor_ohs::setScenarioIndex( SCENE_INDEX* p_scenx_index )
{
	if( p_scenx_index == NULL ) { return false; }
	//シナリオインデックスのコピー
	memcpy( mScenario, p_scenx_index, SCENARIO_CPY_SIZE );
	return true;
}
//現行インデックス取得
UCHR ScenarioConductor_ohs::getID() { return mScenarioID; }

