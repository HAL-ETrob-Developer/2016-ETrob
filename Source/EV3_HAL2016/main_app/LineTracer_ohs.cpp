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
    mLineTraceGo = false;
    mRapidMode  = false;

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
void LineTracer_ohs::postLineTraceConduct( BOOL rapid_mode ) {
    mLineTraceGo = true;
    mRapidMode   = rapid_mode;
    return;
}

/**
 * ライントレース停止指示
 */
void LineTracer_ohs::postLineTraceStop() {
    mLineTraceGo = false;
    // mRunLineCalculator->setParametersInit();
    return;
}

/**
 * ライン探索実行 ＠死にメソッド
 */
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
    mRunningAdmin->postRunning( mSpeed, mDeg, true,false );//(走行速度,走行角度,バランス制御の有無)
}

/**
 * ライントレース実行
 */
void LineTracer_ohs::callLineTraceAct() {
    static ULNG ulClrCounter = 0;
    BOOL BrakeF_ = mRapidMode;

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
    }

    //走行指示
    /* (走行速度,走行角度,バランス制御の有無,ブレーキ) */
    mRunningAdmin->postRunning( mSpeed, mDeg, true, BrakeF_ );

    return;
}

/**
 * ラインエッジトレース
 */
void LineTracer_ohs::execLineEdgeTrace() {
    /* 光学反射値の取得 */
    int16_t sRefVal = mRayReflectAdmin->getValue();

    /* ライン探索ゲインのリセット */
    mGain = 0;
    /* 左右モータの実指示値を取得(保留) */
    mSpeed = mRunningAdmin->getSpeed();
    mDeg   = mRunningAdmin->getVector();

    /* PID計算 */
    mRunLineCalculator->calcRunLine( mRapidMode ,sRefVal, &mSpeed, &mDeg );
    /* 走行速度 */
    // if( mSpeed > LT_MAX_SPEED ){
    //     mSpeed = LT_MAX_SPEED;
    // } else if( mSpeed < LT_MIN_SPEED ) {
    //     mSpeed = LT_MIN_SPEED;
    // }
    /* 角度の決定 */
    if( mDeg > LT_MAX_DEGRE ){
        mDeg = LT_MAX_DEGRE;
    } else if( mDeg < LT_MIN_DEGRE ) {
        mDeg = LT_MIN_DEGRE;
    }
}

/**
 * ラインサーチ＠死にメソッド
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