/* by ohs50465 T.Ueno */

#ifndef MAINAPP_LINETRACER_OHS_H_
#define MAINAPP_LINETRACER_OHS_H_

#include "../calculation/RunLineCalculator_ohs.h"
#include "../device_ope/RunningAdmin_ohs.h"
#include "../device_ope/RayReflectAdmin_ohs.h"

#define LT_SPEED_SLT (       50 )
#define LT_DEGRE_SLT (       30 )

#define LT_MAX_SPEED (      100 )
#define LT_MIN_SPEED (     -100 )
#define LT_MAX_DEGRE (       50 )
#define LT_MIN_DEGRE (      -50 )
#define RISE         (      0.01)
#define SEARCH_SW    (    10000 )

class LineTracer_ohs {
public:
    //生成
    LineTracer_ohs( RunningAdmin_ohs* running_admin, RayReflectAdmin_ohs* ray_reflect_adomin, RunLineCalculator_ohs* running_line_calculator );
    //デストラクタ 死ぬときあるよ
    ~LineTracer_ohs();

    void postLineTraceConduct();
    void postLineTraceStop();
    void callLineTraceAct();
    void callSimplLineTraceAct();

private:
    //メソッド
    void execLineEdgeTrace();
    void execLineSearch();
    //メンバ
    RunningAdmin_ohs*      mRunningAdmin;
    RayReflectAdmin_ohs*   mRayReflectAdmin;
    RunLineCalculator_ohs* mRunLineCalculator;

    SENC_CLR mGetColor;
    BOOL   mLineTraceGo;
    FLOT   mGain;
    int8_t mSpeed;
    int8_t mDeg;

};

#endif  // MAINAPP_LINETRACER_OHS_H_