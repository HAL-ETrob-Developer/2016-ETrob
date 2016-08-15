#include "hal_ev3_std.h"

#include "PatternSequencer_ohs.h"

/**
 * コンストラクタ
 */
ScenarioConductor_ohs::ScenarioConductor_ohs( BodyStateAdmin_ohs* body_state_admin, LineTracer_ohs* line_tracer, PatternSequencer_ohs* pattern_sequencer )
:mBodyStateAdmin( body_state_admin ),
 mLineTracer( line_tracer ),
 mPatternSequencer( pettern_sequencer )
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
	mCheckMethod[CLS_BLK] = checkRayRef;
	mCheckMethod[CLS_GRY] = checkRayRef;
	mCheckMethod[CLS_WHT] = checkRayRef;
	mCheckMethod[RUN_MLG] = checkMileage;
	mCheckMethod[EV3_DEG] = checkAngle;
	mCheckMethod[TIL_DEG] = checkTailDeg;
	mCheckMethod[GYR__ST] = checkGyro;
	mCheckMethod[GYR_UST] = checkGyro;
	mCheckMethod[EX_SLIP] = checkQuit;
	mCheckMethod[EX_END]  = checkSlip;
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

	//インデックスチェック
	if( mScenarioID >= SCENARIO_MAX_NUM ) { return false; }

	/* シナリオ達成チェック ------------------------------------------- */
	//達成確認
	nextEventF = ( *mCheckMethod[( mScenario[mScenarioID].move_event )] )();

	//達成フラグのチェック
	if( nextEventF ) { 
		//シナリオ更新(異常値返却ならば終了)
		if( !setScenarioUpDate()) { return false; }
	}

	/* シナリオ実行 ------------------------------------------- */
	if( mScenario[mScenarioID].pattern_id < PATTERN_ID_MAX  ) {
		//ライントレーサに終了通知を渡す
		mLineTracer->postLineTraceStop();
		//パターンシーケンス指示
		mPatternSequencer->callPatternRunning( mScenario[mScenarioID].pattern_id );
	} else {
		//ライントレース指示
		mLineTracer->postLineTraceConduct();
	}

	//正常終了
	return true;
}

/* 光学センサの状態を確認 */
BOOL ScenarioConductor_ohs::checkRayRef() {
	SENC_CLR getSencClr = mBodyStateAdmin->getColorSensorState();

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
		default:
			break;
	}

	return false;
}
/* 走行距離を確認 */
BOOL ScenarioConductor_ohs::checkMileage() {

}
/* 走行体角度を確認 */
BOOL ScenarioConductor_ohs::checkAngle() {

}
/* 尻尾角度を確認 */
BOOL ScenarioConductor_ohs::checkTailDeg() {

}
/* ジャイロ状態を確認 */
BOOL ScenarioConductor_ohs::checkGyro() {
	SENC_CLR getGyroState = mBodyStateAdmin->getBalanceState();

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
BOOL ScenarioConductor_ohs::checkQuit() {
	//終了操作
	quitCommand();
	return true;
}
/* シナリオ現状を保持する（外部入力待ち） */
BOOL ScenarioConductor_ohs::checkSlip() {
	return false;
}


/**
 * シナリオセット
 */
BOOL ScenarioConductor_ohs::setScenario( UCHR uc_scen_no ) {
	//指定インデックスが範囲内
	if( uc_scen_no < SCENARIO_MAX_NUM ) {
		mScenarioID = uc_scen_no;
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
}

/**
 * シナリオ更新
 */
BOOL ScenarioConductor_ohs::setScenarioUpDate() {
	//インデックスチェック
	if( mScenarioID >= SCENARIO_MAX_NUM ) { return false; }

	//次のシナリオへ
	mScenarioID = mScenario[mScenarioID].next_scene;

	//シナリオ範囲オーバチェック
	if( mScenarioID >= SCENARIO_MAX_NUM; ) {
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