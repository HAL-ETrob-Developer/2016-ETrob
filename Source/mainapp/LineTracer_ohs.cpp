#include "LineTracer_ohs.h"

/**
 * コンストラクタ
 */
LineTracer_ohs::LineTracer_ohs( RayReflectAdomin_ohs* ray_reflect_adomin )
{
    mRayReflectAdomin = ray_reflect_adomin;

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
    numColor = mRayReflectAdomin -> getState();
    /* ラインが白か否かの判別 */
    if(numColor == COLOR_WHITE) {
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

    /* 光学センサ値の取得 */
    
    /* 左右モータの実指示値を取得 */

    /* PID計算 */

    /* 走行速度・角度の決定 */
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
