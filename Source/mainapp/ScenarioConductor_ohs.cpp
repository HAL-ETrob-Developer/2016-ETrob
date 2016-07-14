#include "ContestScenarioConductor_ohs.h"

/**
 * コンストラクタ
 */
ScenarioConductor_ohs::ScenarioConductor_ohs( LineTracer_ohs* line_tracer )
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
void ScenarioConductor_ohs::execScenario() {
    mLineTracer -> postLineTraceConduct();
}

/**
 * 指揮終了
 */
void ScenarioConductor_ohs::quitCommand() {
	
}

/**
 * シナリオセット
 */
void ScenarioConductor_ohs::setScenario() {

}

/**
 * シナリオ更新
 */
void ScenarioConductor_ohs::setScenarioUpDate() {
}
