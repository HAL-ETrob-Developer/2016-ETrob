/* ---------------------------------------------------------------------------------------------- */
// ScenarioConductor_ohs.cpp
// EV3_HAL2016\基本機能\シナリオ指揮者
// 競技内容を突破するシナリオを元に、「EvStateAdmin_ohs」「LineTracer_ohs」「PatternSequencer_ohs」
// 「TrackCompass_ohs」に適切な指示を行う。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// SC0000  2016/08/06  上野　徹    新規作成
// SC0001  2016/08/15  大塚　信晶  修正
// SC0002  2016/08/16  大塚　信晶  関数ポインタ記述
// SC0003  2016/08/20  大塚　信晶  設定ファイル取り込み対応化
// SC0004  2016/09/13  大塚　信晶  シナリオ遷移条件の追加「CLS_LIN」
// SC0005  2016/09/15  大塚　信晶  シナリオ遷移条件の追加「EX_JUMP」「RAXIS_T」
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include "ev3api.h"
#include "hal_ev3_std.h"

#include "ScenarioConductor_ohs.h"

extern FILE* gBtHandle;//デバッグ用

/* ---------------------------------------------------------------------------------------------- */
// クラス名     : ScenarioConductor_ohs
// 役割名       : シナリオコンダクター
// 役割概要     : 競技突破の為に構成されたシナリオに従い状態遷移を管理する。
// 作成日       : 2016/08/06  上野　徹    新規作成
//                2016/08/15  大塚　信晶  修正
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]EvStateAdmin_ohs* ev_state_admin : 本体状態管理
// [I N]LineTracer_ohs* line_tracer      : ライントレーサ
// [I N]PatternSequencer_ohs* pettern_sequencer : 定量走行者
// [I N]TrackCompass_ohs* track_compass  : コース基軸走行
/* ---------------------------------------------------------------------------------------------- */
ScenarioConductor_ohs::ScenarioConductor_ohs( EvStateAdmin_ohs* ev_state_admin, LineTracer_ohs* line_tracer, PatternSequencer_ohs* pettern_sequencer, TrackCompass_ohs* track_compass )
:mEvStateAdmin( ev_state_admin ),       /* 本体状態管理＠コンストラクタ優先処理 */
 mLineTracer( line_tracer ),            /* ライントレーサ＠コンストラクタ優先処理 */
 mPatternSequencer( pettern_sequencer ),/* 定量走行者＠コンストラクタ優先処理 */
 mTrackCompass( track_compass )         /* コース基軸走行＠コンストラクタ優先処理 */
{
	// シナリオ保存構造体のクリア
	memset( mScenario, 0, sizeof(mScenario));
	//初期待機状態の入力
	mScenario[INIT_SCENARIO_ID].move_event = EX_SLIP;// シナリオ保持
	mScenario[INIT_SCENARIO_ID].pattern_id = 0;// 走行パターンIDを0番で開始
	mScenario[INIT_SCENARIO_ID].next_scene = INIT_SCENARIO_ID;// 次のシナリオを自身へ（適当）
	mScenario[INIT_SCENARIO_ID].event_value = 0;// シナリオ達成値は未指定（適当）

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

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : ~ScenarioConductor_ohs
// 機能名       : デストラクタ
// 機能概要     : オブジェクトの破棄
// 作成日       : 2016/08/06  上野　徹    新規作成
/* ---------------------------------------------------------------------------------------------- */
ScenarioConductor_ohs::~ScenarioConductor_ohs() {}

/* パブリック ----------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : execScenario
// 機能名       : シナリオ走行実行
// 機能概要     : シナリオインデックスを参照し状態遷移を行う
// 作成日       : 2016/08/06  上野　徹    新規作成
//                2016/08/15  大塚　信晶  修正
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true :正常終了
// false:遷移終了
/* ---------------------------------------------------------------------------------------------- */
BOOL ScenarioConductor_ohs::execScenario()
{
	/* ------------------------------------------------------------------------------------------ */
	// 変数宣言
	/* ------------------------------------------------------------------------------------------ */

	BOOL nextEventF  = false;// シナリオ達成フラグ
	UCHR ucMoveEvent = mScenario[mScenarioID].move_event;// シナリオ移行イベント

	/* ------------------------------------------------------------------------------------------ */
	// IDチェック
	/* ------------------------------------------------------------------------------------------ */
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

	/* 転倒検知シナリオ終了＠テスト中は停止するといいよ */
#ifdef FALLING_STOP
	if( mEvStateAdmin->getBalanceState() == GSTA_FALLING ) { quitCommand(); }
#endif

	/* ------------------------------------------------------------------------------------------ */
	// シナリオ実行
	/* ------------------------------------------------------------------------------------------ */

	/* 動作パターン確認 ------------------------------------------------------------------------- */
	if( mScenario[mScenarioID].pattern_id < PATTERN_NUM  ) {
		/* パターンシーケンサ範囲 */
		mLineTracer->postLineTraceStop();//ライントレーサに終了通知を渡す
		mPatternSequencer->callPatternRunning( mScenario[mScenarioID].pattern_id );//パターンシーケンス指示
	} else {
		/* パターンシーケンサ範囲外 */
		/* ライントレーサ・トラックコンパス使用 ------------------------------------------------- */
		switch( mScenario[mScenarioID].pattern_id ) {
			case LINETRACER_NORMAL://ライントレース指示＠通常
				mLineTracer->postLineTraceConduct( false );
				break;
			case LINETRACER_SPEED://ライントレース指示＠高速
				mLineTracer->postLineTraceConduct( true );
				break;
			case TRACKCOMPASS_CHECK://方位想定回転＠原位置セット
				mTrackCompass->setReferenceAxis();
				break;
			case TRACKCOMPASS_TRUN://方位想定回転＠回転
				mLineTracer->postLineTraceStop();//ライントレーサに終了通知を渡す
				mTrackCompass->callRAxisTurn(( int32_t )( mScenario[mScenarioID].event_value ));
				break;
			case TRACKCOMPASS_MOVEB://方位想定前後進＠倒立
				mLineTracer->postLineTraceStop();//ライントレーサに終了通知を渡す
				mTrackCompass->callRAxisMove(( int32_t )( mScenario[mScenarioID].event_value ), true );
				break;
			case TRACKCOMPASS_MOVE://方位想定前後進＠支え有り
				mLineTracer->postLineTraceStop();//ライントレーサに終了通知を渡す
				mTrackCompass->callRAxisMove(( int32_t )( mScenario[mScenarioID].event_value ), false );
				break;
			default:
				break;
		}
	}

	/* ------------------------------------------------------------------------------------------ */
	// シナリオ達成チェック
	/* ------------------------------------------------------------------------------------------ */

	/* 本体状態管理を更新 ----------------------------------------------------------------------- */
	if( mEvStateAdmin->setStateCollection() == false ) {
		return true;//状態変化無しなら終了
	}
	/* 達成確認＠関数ポインター使ってます */
	nextEventF = ( this->*mCheckMethod[ucMoveEvent] )();//登録されたメソッドの使用

	/* 達成フラグのチェック */
	if( nextEventF == true ) { 
		//シナリオ更新(異常値返却ならば終了)
		if( setScenarioUpDate() == false ) { return false; }

#ifdef TRANSITION_SOUND
		ev3_speaker_play_tone( NOTE_B6, 80 );
		// デバック挿入
		fprintf( gBtHandle,"ID      [%d]\r\n",(int)getID());
		fprintf( gBtHandle,"Mileage [%d]\r\n",(int)mEvStateAdmin->getMileage());
		fprintf( gBtHandle,"Angle   [%d]\r\n",(int)mEvStateAdmin->getBodyAngle());
#endif
	}

	return true;//正常終了
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : setScenario
// 機能名       : シナリオID外部変更
// 機能概要     : 現行シナリオIDを外部から強制変更する
// 作成日       : 2016/08/15  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]UCHR uc_scen_no : シナリオID
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true :正常終了
// false:指定範囲外
/* ---------------------------------------------------------------------------------------------- */
BOOL ScenarioConductor_ohs::setScenario( UCHR uc_scen_no )
{
	/* 指定インデックス範囲確認 */
	if( uc_scen_no < SCENARIO_MAX_NUM ) {
		// 範囲内
		mScenarioID = uc_scen_no;// ID変更
		mEvStateAdmin->setStateRefresh();//本体状態管理のリフレッシュ
		return true;// 正常終了
	}
	return false;// 異常終了	
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : quitCommand
// 機能名       : システム終了
// 機能概要     : シナリオ実行を終了し、全機能に終了を通知する
// 作成日       : 2016/08/15  大塚　信晶  新規作成
/* ---------------------------------------------------------------------------------------------- */
void ScenarioConductor_ohs::quitCommand()
{
	//シナリオインデックスを範囲外にする = 終了
	mScenarioID = SCENARIO_MAX_NUM;
	//ライントレーサに終了通知を渡す
	mLineTracer->postLineTraceStop();
	//パターンシーケンサに終了通知を渡す
	mPatternSequencer->callSequencStop();
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : setScenarioUpDate
// 機能名       : シナリオ更新
// 機能概要     : シナリオを次へ遷移させる
// 作成日       : 2016/08/15  大塚　信晶  新規作成
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true :正常遷移
// false:遷移終了
/* ---------------------------------------------------------------------------------------------- */
BOOL ScenarioConductor_ohs::setScenarioUpDate()
{
	/* インデックスチェック */
	if( mScenarioID >= SCENARIO_MAX_NUM ) { return false; }// シナリオ範囲外＠終了

	mEvStateAdmin->setStateRefresh();// 本体状態管理のリフレッシュ

	mScenarioID = mScenario[mScenarioID].next_scene;// 次のシナリオへ

	/* シナリオ範囲オーバチェック */
	if( mScenarioID >= SCENARIO_MAX_NUM ) {
		quitCommand();// 終了操作
		return false;// 遷移終了を通知
	}

	return true;// 正常終了
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : setScenarioIndex
// 機能名       : シナリオ登録
// 機能概要     : シナリオを保存した構造体を取り込む
// 作成日       : 2016/08/15  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]SCENE_INDEX* p_scenx_index : シナリオ構造体
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true :正常終了
// false:異常終了
/* ---------------------------------------------------------------------------------------------- */
BOOL ScenarioConductor_ohs::setScenarioIndex( SCENE_INDEX* p_scenx_index )
{
	if( p_scenx_index == NULL ) { return false; }// ぬるぽ
	//シナリオインデックスのコピー
	memcpy( mScenario, p_scenx_index, SCENARIO_CPY_SIZE );// &mScenario[0]に変更したい…
	return true;// 正常終了
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : getID
// 機能名       : 現行シナリオID取得
// 機能概要     : 現行のシナリオIDを出力する
// 作成日       : 2016/08/15  大塚　信晶  新規作成
/* 戻り値 [UCHR] -------------------------------------------------------------------------------- */
// 0～SCENARIO_MAX_NUM : 現行シナリオID
/* ---------------------------------------------------------------------------------------------- */
UCHR ScenarioConductor_ohs::getID() { return mScenarioID; }

/* プライベート --------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkRayRef
// 機能名       : 光学センサ状態確認
// 機能概要     : mEvStateAdminより光学センサの状態を取得し、シナリオ遷移条件の達成を確認する
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:未達
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkRayRef()
{
	SENC_CLR getSencClr = mEvStateAdmin->getColorSensorState();// カラー取得

	/* 達成条件確認項目の判断 */
	switch( mScenario[mScenarioID].move_event ) {
		case CLS_BLK:// 黒チェック
			if( getSencClr == SCLR_BLACK ) { return true; }// 黒検知
			break;
		case CLS_GRY:// 灰チェック
			if( getSencClr == SCLR_GRAY ) { return true; }// 灰検知
			break;
		case CLS_WHT:// 白チェック
			if( getSencClr == SCLR_WHITE ) { return true; }// 白検知
			break;
		case CLS_LIN:// ラインチェック
			if( getSencClr != SCLR_WHITE ) { return true; }// 白以外を検知
			break;
		default:
			break;
	}

	return false;// 条件未達
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkMileage
// 機能名       : 走行距離達成確認
// 機能概要     : mEvStateAdminより走行距離を取得し、シナリオ遷移条件の達成を確認する
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:未達
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkMileage()
{
	SLNG lGetNowMlg = ( SLNG )mEvStateAdmin->getMileage();// 現在走行距離取得
	SLNG lTargetMlg = mScenario[mScenarioID].event_value; // 目標距離取得

	/* 目標方向確認＠前進・後進 */
	if( lTargetMlg > 0 ) {
		//前進チェック
		if( lGetNowMlg > lTargetMlg ) { return true; }
	} else {
		//後進チェック＠if( lGetNowMlg <= lTargetMlg )も検討してください
		if( lGetNowMlg < lTargetMlg ) { return true; }
	}

	return false;// 条件未達
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkAngle
// 機能名       : 旋回角度達成確認
// 機能概要     : mEvStateAdminより旋回角度を取得し、シナリオ遷移条件の達成を確認する
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:未達
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkAngle()
{
	SLNG lGetNowDeg = ( SLNG )mEvStateAdmin->getBodyAngle();// 現在旋回方向取得
	SLNG lTargetDeg = mScenario[mScenarioID].event_value;   // 目標方向取得

	/* 旋回方向判断 */
	if( lTargetDeg > 0 ) {
		//cwチェック
		if( lGetNowDeg > lTargetDeg ) { return true; }
	} else {
		//ccwチェック＠if( lGetNowDeg <= lTargetDeg )も検討してください
		if( lGetNowDeg < lTargetDeg ) { return true; }
	}

	return false;// 条件未達
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkTailDeg
// 機能名       : 尻尾角度達成確認
// 機能概要     : mEvStateAdminより尻尾角度を取得し、シナリオ遷移条件の達成を確認する
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:未達
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkTailDeg()
{
	SLNG lGetNowDeg = ( SLNG )mEvStateAdmin->getTailAngle();// 現在尻尾角度
	SLNG lTrgDegMax = 0;// 目標尻尾角度許容範囲＠最大
	SLNG lTrgDegMin = 0;// 目標尻尾角度許容範囲＠最小

	/* 目標達成範囲の設定 */
	lTrgDegMax = mScenario[mScenarioID].event_value + TIL_DEG_PERMISSION; 
	lTrgDegMin = mScenario[mScenarioID].event_value - TIL_DEG_PERMISSION;

	/* 目標角範囲達成確認 */
	if(( lTrgDegMax > lGetNowDeg ) && ( lGetNowDeg > lTrgDegMin )) { return true; }

	return false;// 条件未達
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkGyro
// 機能名       : 本体角速度達成確認
// 機能概要     : mEvStateAdminより本体安定度を取得し、シナリオ遷移条件の達成を確認する
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:未達
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkGyro()
{
	GYRO_STATE getGyroState = mEvStateAdmin->getBalanceState();// 本体安定度の取得

	/* 達成条件確認項目の判断 */
	switch( mScenario[mScenarioID].move_event ) {
		case GYR__ST:// 安定状態
			if( getGyroState == GSTA_STABILITY ) { return true; }
			break;
		case GYR_UST:// 不安定状態
			if( getGyroState == GSTA_UNSTABLE ) { return true; }
			break;
		default:
			break;
	}
	
	return false;// 条件未達
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkQuit
// 機能名       : シナリオ終了
// 機能概要     : 状態遷移を終了する
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:無し
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkQuit() {
	//終了操作
	quitCommand();
	return true;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkSlip
// 機能名       : 状態保持
// 機能概要     : 条件達成フラグを出力しない。（外部指示待ち）
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :無し
// false:条件未達
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkSlip() { return false; }

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkJump
// 機能名       : 状態移行
// 機能概要     : 条件達成フラグを出力する（別シナリオへのバイパス用＠TRACKCOMPASS_CHECKとの連携）
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:無し
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkJump() { return true; }

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : checkRAxisTurn
// 機能名       : 基軸旋回達成確認
// 機能概要     : 基軸旋回にて指定旋回値に達しているか確認する。
// 作成日       : 2016/08/16  大塚　信晶  新規作成
/* 戻り値 [bool] -------------------------------------------------------------------------------- */
// true :条件達成
// false:無し
/* ---------------------------------------------------------------------------------------------- */
bool ScenarioConductor_ohs::checkRAxisTurn()
{
	return ( bool )mTrackCompass->getRAxisTurnFinish( mScenario[mScenarioID].event_value );
}

/* 関数ポインタ系のエラーコメント置いときますね */
// ../workspace/EV3_HAL2016/main_app/ScenarioConductor_ohs.cpp:33:24: error: cannot convert 'ScenarioConductor_ohs::checkSlip' from type 'bool (ScenarioConductor_ohs::)(int)' to type 'bool (ScenarioConductor_ohs::*)()'

/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
