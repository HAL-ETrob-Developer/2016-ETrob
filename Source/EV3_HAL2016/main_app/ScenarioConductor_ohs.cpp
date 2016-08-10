#include "hal_ev3_std.h"

#include "LineTracer_ohs.h"
#include "ScenarioConductor_ohs.h"
#include "../device_ope/RayReflectAdmin_ohs.h"

#include "LineTracer_ohs.h"
#include "PatternSequencer_ohs.h"

/**
 * コンストラクタ
 */
ScenarioConductor_ohs::ScenarioConductor_ohs( LineTracer_ohs* line_tracer, BodyStateAdmin_ohs* body_state_admin, PatternSequencer_ohs* pattern_sequencer )
{
	mLineTracer 			= line_tracer;
	mBodyStateAdmin 	= body_state_admin;
	mPatternSequencer = pettern_sequencer;

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

	/* 実行動作インデックスの番号に応じて指揮する */
	switch ( mIndex.action_number ) {
		case LINE_TRACE;
		/*　ライントレース指揮 */
		mLineTracer -> postLineTraceConduct();
		break;

		case PATTERN_RUNNING;
		/* 定量走行指揮 */
		mPatternSequencer -> callPatternRunning();
		break;
	}

	/* 本体状態更新 */
	mBodyStateAdmin -> setBodyStateUpdate();

	/* カラーセンサ状態取得 */
	mColorSensorState = mBodyStateAdmin -> getColorSensorState();

	/* バランス状態取得 */
	mBalanceState = mBodyStateAdmin -> getBalanceState();

	/* 走行距離取得 */
	mMilage = mBodyStateAdmin -> getMileage();

	/* 本体角度取得 */
	mBodyAngle = mBodyStateAdmin -> getBodyAngle();

	/* 尾角度取得 */
	mTailAngle = mBodyStateAdmin -> getTailAngle();

	//グレー検知したら達成条件を更新する
	if( mColorSensorState == SCLR_GRAY ) {
		mIndex.event_condition++;
		switch( mIndex.event_condition ) {
			case TRACE_CLEAR:			//トレースクリア
				/* 現本体状態の記録 ------------------------------------------- */
				ColorSensorState = mColorSensorState;
				BalanceState		 = mBalanceState;
				Milage					 = mMilage;
				BodyAngle				 = mBodyAngle;
				TailAngle				 = mTailAngle;

				setScenarioUpDate();//シナリオ更新
			break;

			case HURDLE1_CLEAR:		//難所1（ルックアップゲートor階段）クリア
				/* 現本体状態の記録 ------------------------------------------- */
				ColorSensorState = mColorSensorState;
				BalanceState		 = mBalanceState;
				Milage					 = mMilage;
				BodyAngle				 = mBodyAngle;
				TailAngle				 = mTailAngle;

				setScenarioUpDate();//シナリオ更新
				break;

			case HURDLE2_CLEAR:		//難所2(ガレージイン)クリア
				quitCommand();			//指揮終了
				break;

			default:							//トレース中
				setScenario( mRoute );
				break;
		}
	}
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
	if ( route == RROUTE_LEFT ) {
		switch ( flow_transition ) {
			case TRACE;
				/* トレース */
				break;
			case HURDLE1;
				/* ルックアップゲート */
				break;
			case HURDLE2;
				/* ガレージイン */
				break;
		}
	}
	else if (route == RROUTE_RIGHT ) {
		switch ( flow_transition ) {
			case TRACE;
				/* トレース */
				break;
			case HURDLE1;
				/* 階段 */
				break;
			case HURDLE2;
				/* ガレージイン */
				break;
		}
	}
}

/**
 * シナリオ更新
 */
void ScenarioConductor_ohs::setScenarioUpDate() {
	flow_transition++;
}
