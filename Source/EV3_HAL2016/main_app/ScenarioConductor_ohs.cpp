#include "hal_ev3_std.h"

#include "LineTracer_ohs.h"
#include "ScenarioConductor_ohs.h"
#include "../device_ope/RayReflectAdmin_ohs.h"

#include "LineTracer_ohs.h"
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
	mScenario[INIT_SCENARIO_ID].next_scene = 0;
	mScenario[INIT_SCENARIO_ID].pattern_id = 0;
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
<<<<<<< HEAD
=======


}

/* 光学センサの状態を確認 */
void ScenarioConductor_ohs::checkRayRef() {

}
/* 走行距離を確認 */
void ScenarioConductor_ohs::checkMileage() {

}
/* 走行体角度を確認 */
void ScenarioConductor_ohs::checkAngle() {

}
/* 尻尾角度を確認 */
void ScenarioConductor_ohs::checkTailDeg() {

}
/* ジャイロ状態を確認 */
void ScenarioConductor_ohs::checkGyro() {

}
/* シナリオ終了操作 */
void ScenarioConductor_ohs::checkQuit() {
	//シナリオインデックスを範囲外にする = 終了
	mScenarioID = SCENARIO_MAX_NUM;
}
/* シナリオ現状を保持する（外部入力待ち） */
void ScenarioConductor_ohs::checkSlip() {
	return;
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
>>>>>>> fa7f2176a8d229e984b1e244e7356a4d15e0aa5a
}

/**
 * 指揮終了
 */
void ScenarioConductor_ohs::quitCommand() {
<<<<<<< HEAD
	/* システム終了通知をメインタスクへ */
}

/**
 * シナリオセット
 */
SCHR ScenarioConductor_ohs::setScenario( RUNNING_ROUTE route ) {

=======
>>>>>>> fa7f2176a8d229e984b1e244e7356a4d15e0aa5a
}

/**
 * シナリオ更新
 */
void ScenarioConductor_ohs::setScenarioUpDate() {
	flow_transition++;
}
