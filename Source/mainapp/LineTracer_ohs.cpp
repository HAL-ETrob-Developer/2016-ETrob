#include "LineTracer_ohs.h"

/**
 * コンストラクタ
 */
LineTracer_ohs::LineTracer_ohs( RayReflectAdomin_ohs* ray_reflect_adomin, RunningLineCalculator_ohs* running_line_calculator )
{
public:
    mRayReflectAdomin     = ray_reflect_adomin;
    mRunningLineCalclator = running_line_calclator;
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
    public:
    /* 光学反射値の取得 */
    SENC_CLR = mRayReflectAdomin -> getReflectValue();
    /* ラインが白か否かの判別 */
    if(SENC_CLR == SCLR_WHITE) {
    /* 白ならラインエッジトレースへ */
    execLineEdgeTrace();
    }
    else {
    /* 白以外ならライン探索へ */
    execLineSearch();
    }
    private:
    
}

/**
 * ライントレース実行
 */
void LineTracer_ohs::callLineTraceAct() {

}

/**
 * ラインエッジトレース
 */
void LineTracer_ohs::execLineEdgeTrace() {
    /* ライン探索ゲインのリセット */
    mGain = 0;
    /* 光学センサ値の取得 */
    mRayReflectAdomin -> getReflectState();
    /* 左右モータの実指示値を取得(保留) */

    /* PID計算 */
    mRunningLineCalculator -> calcRunningLine;
    /* 走行速度・角度の決定 */
    mRunningAdmin -> getTheRunningPWM;
    mRunningAdmin -> getRunningAngle;
}

/**
 * ラインサーチ
 */
void LineTracer_ohs::execLineSearch() {
    /* ライン探索ゲインの取得 */

    /* ゲイン比に基づき走行速度減 */

    /* ゲイン比に基づき走行角度をCCWへ */

    /* ライン探索ゲインの上昇 */    
}
