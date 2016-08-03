#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "ContestScenarioConductor_ohs.h"

/**
 * コンストラクタ
 */
ScenarioConductor_ohs::ScenarioConductor_ohs( LineTracer_ohs* line_tracer, BodyStateAdmin_ohs* body_state_admin )
{
	mLineTracer = line_tracer;
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

		/* 1.シナリオチェック */
		/* 1-1.現・本体状態の取得 */
    body_state_admin -> setBodyStateUpdate();

		/* 1-2.現・シナリオ取得 */


}

/**
 * 指揮終了
 */
void ScenarioConductor_ohs::quitCommand() {

}

/**
 * 現・本体状態の記録
 */
void ScenarioConductor_ohs::setScenario() {

}

/**
 * シナリオ更新
 */
void ScenarioConductor_ohs::setScenarioUpDate() {
}
