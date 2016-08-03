/* by ohs50465 T.Ueno */

#ifndef MAINAPP_LINETRACER_OHS_H_
#define MAINAPP_LINETRACER_OHS_H_

#define MAX_SPEED (      100 )
#define MIN_SPEED (     -100 )
#define MAX_DEGRE (       50 )
#define MIN_DEGRE (      -50 )
#define RISE      (      0.01)

class LineTracer_ohs {
public:
    //生成
    LineTracer_ohs( RunningAdmin_ohs* running_admin, RayReflectAdomin_ohs* ray_reflect_adomin, RunningLineCalculator_ohs* running_line_calculator );
    //デストラクタ
    ~LineTracer_ohs();

    void postLineTraceConduct();
    void callLineTraceAct();

private:
    //メソッド
    void execLineEdgeTrace();
    void execLineSearch();
    //メンバ
    RunningAdmin_ohs* mRunningAdmin;
    RayReflectAdomin_ohs*  mRayReflectAdomin;
    RunningLineCalculator_ohs*  mRunningLineCalclator;
    SENC_CLR mGetColor;
    BOOL mLineTraceGo;
    int8_t mSpeed;
    int8_t mDeg;
    int8_t mGain;

};

#endif  // MAINAPP_LINETRACER_OHS_H_
