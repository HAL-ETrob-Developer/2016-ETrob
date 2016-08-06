#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "ContestScenarioConductor_ohs.h"

#include "LineTracer_ohs.h"
#include "PatternSequencer_ohs.h"

/**
 * コンストラクタ
 */
ScenarioConductor_ohs::ScenarioConductor_ohs( LineTracer_ohs* line_tracer, BodyStateAdmin_ohs* body_state_admin, PatternSequencer_ohs* pattern_sequencer )
{
	/* 状態遷移インデックス構造体初期化 */
	memset( mNow, 0, sizeof( BODY_STATE ) ;

	mLineTracer 			= line_tracer;
	mBodyStateAdmin 	= body_state_admin;
	mPatternSequencer = pettern_sequencer;
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

	/*　ライントレース指揮 */
	mLineTracer -> postLineTraceConduct();

	/* 定量走行指揮 */
	mPatternSequencer -> callPatternRunning( /* 保留 */ );

	/* 本体状態更新 */
	mBodyStateAdmin -> setBodyStateUpdate();

	/* カラーセンサ状態取得 */
	mBodyStateAdmin -> getColorSensorState();

	/* バランス状態取得 */
	 mBodyStateAdmin -> getBalanceState();

	/* 走行距離取得 */
	mBodyStateAdmin -> getMileage();

	/* 本体角度取得 */
	mBodyStateAdmin -> getBodyAngle();

	/* 尾角度取得 */
	mBodyStateAdmin -> getTailAngle();
}

/**
 * 指揮終了
 */
void ScenarioConductor_ohs::quitCommand() {
	/* 保留 */
}

/**
 * シナリオセット
 */
SCHR ScenarioConductor_ohs::setScenario() {
	/* 保留 */
}

/**
 * シナリオ更新
 */
void ScenarioConductor_ohs::setScenarioUpDate() {
	/* 保留 */
}
