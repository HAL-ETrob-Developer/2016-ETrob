#include "ev3api.h"
#include "hal_ev3_std.h"
#include "RunningAdmin_ohs.h"
#include "RayReflectAdmin_ohs.h"
#include "RunLineCalculator_ohs.h"

#include "LineTracer_ohs.h"

/**
 * コンストラクタ
 */
LineTracer_ohs::LineTracer_ohs( RunningAdmin_ohs* running_admin,RayReflectAdomin_ohs* ray_reflect_adomin, RunningLineCalculator_ohs* running_line_calculator )
:mRunningAdmin(running_admin)
 mRayReflectAdomin( ray_reflect_adomin ),
 mRunningLineCalclator( running_line_calclator )
{
    mGetColor = SCLR_GRAY;
    mSpeed = 0;
    mDeg   = 0;
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
 * ライントレース実行
 */
void LineTracer_ohs::callLineTraceAct() {
    //実行指揮の確認
    if( mLineTraceGo == false ) { return; }//ライントレース指揮無し
    //フラグリセット
    mLineTraceGo = false;

    /* 光学反射値の取得 */
    mGetColor = mRayReflectAdomin->getReflectValue();
    /* ラインが白か否かの判別 */
    if( mGetColor == SCLR_WHITE ) {
        /* 白ならラインエッジトレースへ */
        execLineEdgeTrace();
    } else {
        /* 白以外ならライン探索へ */
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
    FLOT mGain = 0;
    /* 左右モータの実指示値を取得(保留) */

    /* PID計算 */
    mRunningLineCalculator->calcRunningLine( mGetColor, &mSpeed, &mDeg );
    /* 走行速度 */
    if( mSpeed > MAX_SPEED ){
        mSpeed = MAX_SPEED;
    } eise if( mSpeed < MIN_SPEED ) {
        mSpeed = MIN_SPEED;
    }
    /* 角度の決定 */
    if( mDeg > MAX_DEGRE ){
        mDeg = MAX_DEGRE;
    } eise if( mDeg < MIN_DEGRE ) {
        mDeg = MIN_DEGRE;
    }
}

/**
 * ラインサーチ
 */
void LineTracer_ohs::execLineSearch() {
    /* ライン探索ゲインの取得 */
    static FLOT mGain = 0;
    /* ゲイン比に基づき走行速度減 */
    mSpeed = 100.0F - ( 100.0F * mGain );
    /* ゲイン比に基づき走行角度をCCWへ */
    mDeg = ( int8_t )( -50.0F * mGain );
    /* ライン探索ゲインの上昇 */
    mGain += RISE;
    }
