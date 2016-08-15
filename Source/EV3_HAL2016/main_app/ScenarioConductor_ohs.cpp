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


	mCheckMethod[] = 
	mCheckMethod[] = 
	mCheckMethod[] = 
	mCheckMethod[] = 
	mCheckMethod[] = 
	mCheckMethod[] = 
	mCheckMethod[] = 
	mCheckMethod[] = 
	mCheckMethod[] = 
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
 * シナリオセット
 */
SCHR ScenarioConductor_ohs::setScenario(  ) {
}

/**
 * 指揮終了
 */
void ScenarioConductor_ohs::quitCommand() {
}

/**
 * シナリオ更新
 */
void ScenarioConductor_ohs::setScenarioUpDate() {
	flow_transition++;
}
