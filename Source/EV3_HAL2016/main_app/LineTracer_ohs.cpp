#include "ev3api.h"
#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"

/**
 * コンストラクタ
 */
LineTracer_ohs::LineTracer_ohs( RunningAdmin_ohs* running_admin, RayReflectAdmin_ohs* ray_reflect_admin, RunLineCalculator_ohs* run_line_calculator )
:mRunningAdmin(running_admin),
 mRayReflectAdmin( ray_reflect_admin ),
 mRunLineCalculator( run_line_calculator )
{
    mGetColor = SCLR_GRAY;
    mSpeed = 0;
    mDeg   = 0;
    mGain = 0;
}

/**
 * デストラクタ
 */
LineTracer_ohs::~LineTracer_ohs() {
}

/**
 * ライントレース指揮
 */
void LineTracer_ohs::postLineTraceConduct() {
    mLineTraceGo = true;
}

/**
 * ライントレース停止指示
 */
void LineTracer_ohs::postLineTraceStop() {
    mLineTraceGo = false;
}


void LineTracer_ohs::callSimplLineTraceAct() {
    //実行指揮の確認 
    if( mLineTraceGo == false ) { return; }//ライントレース指揮無し
    /* 光学反射値の取得 */
    mGetColor = mRayReflectAdmin->getState();
  
    /* ラインが白か否かの判別 */
    if( mGetColor == SCLR_WHITE ) {
        mDeg = -LT_DEGRE_SLT;
    } else {
        mDeg = LT_DEGRE_SLT;
    }
    //走行速度の決定
    mSpeed = LT_SPEED_SLT;

    //走行指示
    mRunningAdmin->postRunning( mSpeed, mDeg, true );//(走行速度,走行角度,バランス制御の有無)
}

/**
 * ライントレース実行
 */
void LineTracer_ohs::callLineTraceAct() {
    static ULNG ulClrCounter = 0;

    //実行指揮の確認 
    if( mLineTraceGo == false ) { return; }//ライントレース指揮無し

    /* 光学反射値の取得 */
    mGetColor = mRayReflectAdmin->getState();

    /* ラインが白か否かの判別 */
    if( mGetColor == SCLR_WHITE ) { ulClrCounter++; }

    if( ulClrCounter < SEARCH_SW ) {
        execLineEdgeTrace();
        ulClrCounter = 0;
    } else {
        /* 一定以上白を連続して検出 */
        execLineEdgeTrace();
      //  execLineSearch(); ラインサーチ停止test

    }

    //走行指示
    mRunningAdmin->postRunning( mSpeed, mDeg, true );//(走行速度,走行角度,バランス制御の有無)

    return;
}

/**
 * ラインエッジトレース
 */
void LineTracer_ohs::execLineEdgeTrace() {
    /* ライン探索ゲインのリセット */
    mGain = 0;
    /* 左右モータの実指示値を取得(保留) */

    /* PID計算 */
    // mRunLineCalculator->calcRunLine( mGetColor, &mSpeed, &mDeg );
    mRunLineCalculator->calcRunLineUseRefLv( mRayReflectAdmin->getValue(), &mSpeed, &mDeg);
    /* 走行速度 */
    if( mSpeed > LT_MAX_SPEED ){
        mSpeed = LT_MAX_SPEED;
    } else if( mSpeed < LT_MIN_SPEED ) {
        mSpeed = LT_MIN_SPEED;
    }
    /* 角度の決定 */
    if( mDeg > LT_MAX_DEGRE ){
        mDeg = LT_MAX_DEGRE;
    } else if( mDeg < LT_MIN_DEGRE ) {
        mDeg = LT_MIN_DEGRE;
    }
}

/**
 * ラインサーチ
 */
void LineTracer_ohs::execLineSearch()
{
    /* 固定速度で走行 */
    mSpeed = ( int8_t )( 30 );
    /* ゲイン比に基づき走行角度をCCWへ */
    mDeg = ( int8_t )( -50.0F * mGain );
    /* ライン探索ゲインの上昇 */
    mGain += RISE;
}