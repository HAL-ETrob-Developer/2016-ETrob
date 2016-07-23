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
    if( mGetColor == SCLR_WHITE ) { ulClrCounter; }

    if( ulClrCounter < SEARCH_SW ) {
        execLineEdgeTrace();
        ulClrCounter = 0;
    } else {
        /* 一定以上白を連続して検出 */
        execLineSearch();
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
    mRunLineCalculator->calcRunLine( mGetColor, &mSpeed, &mDeg );
    /* 走行速度 */
    if( mSpeed > MAX_SPEED ){
        mSpeed = MAX_SPEED;
    } else if( mSpeed < MIN_SPEED ) {
        mSpeed = MIN_SPEED;
    }
    /* 角度の決定 */
    if( mDeg > MAX_DEGRE ){
        mDeg = MAX_DEGRE;
    } else if( mDeg < MIN_DEGRE ) {
        mDeg = MIN_DEGRE;
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