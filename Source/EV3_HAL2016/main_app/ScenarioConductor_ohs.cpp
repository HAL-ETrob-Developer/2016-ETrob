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

	/* 実行動作インデックスの番号に応じて指揮する */
	switch ( mIndex.action_number ) {
		case LINE_TRACE:        /*　ライントレース指揮 */
		mLineTracer -> postLineTraceConduct();
		break;

		case PATTERN_RUNNING:   /* 定量走行指揮 */
		mPatternSequencer -> callPatternRunning();
		break;

		case LOOKUP_GATE:
		/* 走行体を傾ける */
		mTailAngle = TargetTailAngle;              /* 尾角度指定 */
		TailAdmin -> postTailDegree( mTailAngle ); /* 尾角度指示 */

		/* グレーゾーンからスタートし、ルックアップゲート通過直後の場所まで距離を進める */
		mPatternSequencer -> callPatternRunning();
		if( mMilage >= TargetMilage2 - /* ルックアップゲート通過直後の場所になるよう調整 */ )　{
		/* ルックアップゲート通過前の場所まで後退する */
		while( mMilage >= TargetMilage1 + /*ルックアップゲート手前の場所になるよう調整 */ ) {
			/* 後退処理 */
		}
		/* 次のグレーを検知するまで前進する */
		mPatternSequencer -> callPatternRunning();
		break;

		case STEP:
		/* 1段目に上るため速度を上げる */

		/* 登ったら一旦停止し、右に360度回転する */

		/* 再び走行開始 2段目を上る */

		/* 登ったら一旦停止し、右に360度回転する */

		/* 走行速度を元に戻し、次のグレーを検知するまで前進する */
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

  /* 達成条件更新 --------------------------------------------------- */
	if( mColorSensorState == SCLR_GRAY ) {
		//ゴール後
		if( mMilage >= TargetMilage && mMilage < TargetMilage2 ) {
			mIndex.event_condition = TRACE_CLEAR;
		}

		//ルックアップゲート通過後
		else if( mMilage >= TargetMilage2 && mMilage < TargetMilage3 ) {
			mIndex.event_condition = HURDLE1_CLEAR;
		}


		switch( mIndex.event_condition ) {

      case NO_CLEAR:       //トレース中
				setScenario( mRoute );
				break;

			case TRACE_CLEAR:    //トレースクリア
			/* 現本体状態の記録 ------------------------------------------- */
				ColorSensorState = mColorSensorState;
				BalanceState     = mBalanceState;
				Milage           = mMilage;
				BodyAngle        = mBodyAngle;
				TailAngle        = mTailAngle;


				setScenarioUpDate();//シナリオ更新
				setScenario( mRoute );
			break;

			case HURDLE1_CLEAR:		//難所1（ルックアップゲートor階段）クリア
        TailAdmin -> postTailDegree( TailAngle ); /* 尾角度を元に戻す指示をする */
				/* 現本体状態の記録 ------------------------------------------- */
				ColorSensorState = mColorSensorState;
				BalanceState     = mBalanceState;
				Milage           = mMilage;
				BodyAngle        = mBodyAngle;
				TailAngle        = mTailAngle;


				setScenarioUpDate(); //シナリオ更新
				setScenario( mRoute );
				break;
		}
	}

	//ガレージインの処理
	if( mMilage >= TargetMilage3 ) {
		mIndex.event_condition = HURDLE2_CLEAR;
		/* 3秒間完全停止処理 */
	}

	if(mIndex.event_condition == HURDLE2_CLEAR ) {
			quitCommand(); //指揮終了
			break;
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
				TargetMilage1 = ;/* スタートからゴールまでの距離 */
				break;
			case HURDLE1;
				/* ルックアップゲート */
				mIndex.action_number = LOOKUP_GATE;
				TargetMilage2   = ;/* スタートからルックアップゲート通過後のグレーまでの距離 */
				TargetTailAngle = ;/* ルックアップゲートを通過できる角度 */
				break;
			case HURDLE2;
				/* ガレージイン */
				TargetMilage3 = ;/* スタートからガレージ内停止位置までの距離 */

				break;
		}
	}
	else if ( route == RROUTE_RIGHT ) {
		switch ( flow_transition ) {
			case TRACE;
				/* トレース */
				TargetMilage1 = ;/* スタートからゴールまでの距離 */
				break;
			case HURDLE1;
				/* 階段 */
				mIndex.action_number = STEP;
				TargetMilage2 = ;/* ゴールから階段通過後のグレーまでの距離 */
				break;
			case HURDLE2;
				/* ガレージイン */
				TargetMilage3 = ;/* 階段通過後のグレーからガレージ内停止位置までの距離 */
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
