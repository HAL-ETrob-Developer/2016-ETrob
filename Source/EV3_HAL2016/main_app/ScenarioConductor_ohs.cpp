#include "hal_ev3_std.h"

#include "LineTracer_ohs.h"
#include "ScenarioConductor_ohs.h"
#include "../device_ope/RayReflectAdmin_ohs.h"

#include "LineTracer_ohs.h"
#include "PatternSequencer_ohs.h"

/**
 * コンストラクタ
 */
ScenarioConductor_ohs::ScenarioConductor_ohs( LineTracer_ohs* line_tracer, BodyStateAdmin_ohs* body_state_admin, PatternSequencer_ohs* pattern_sequencer,TailAdmin_ohs* tail_admin, RunningAdmin_ohs* running_admin )
{
	mLineTracer 			= line_tracer;
	mBodyStateAdmin 	= body_state_admin;
	mPatternSequencer = pettern_sequencer;
	mTailAdmin        = tail_admin;
	mRunningAdmin     = running_admin;

	mMilage = 0;
	mBodyAngle = 0;
	mTailAngle = 0;
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
}

/**
 * 指揮終了
 */
void ScenarioConductor_ohs::quitCommand() {
	/* システム終了通知をメインタスクへ */
}

/**
 * シナリオセット
 */
SCHR ScenarioConductor_ohs::setScenario( RUNNING_ROUTE route ) {

}

/**
 * シナリオ更新
 */
void ScenarioConductor_ohs::setScenarioUpDate() {
	flow_transition++;
}
