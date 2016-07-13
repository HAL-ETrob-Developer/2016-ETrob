/* by ohs50465 T.Ueno */

#ifndef MAINAPP_LINETRACER_OHS_H_
#define MAINAPP_LINETRACER_OHS_H_

class LineTracer_ohs {
public:
    //生成
    LineTracer_ohs();
    //デストラクタ 死ぬときあるよ
        virtual ~LineTracer_ohs();

    void postLineTraceConduct();
    void callLineTraceAct();
    void execLineEdgeTrace();
    void execLineSearch();

private:

};

#endif  // MAINAPP_LINETRACER_OHS_H_
