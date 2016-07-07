/* by ohs45025 N.Ohtsuka */

#ifndef MAINAPP_LINETRACER_OHS_H_
#define MAINAPP_LINETRACER_OHS_H_

#include "LineMonitor.h"
#include "BalancingWalker.h"

class LineTracer {
public:
    //生成
    LineTracer();
    //デストラクタ 死ぬときあるよ
        virtual ~LineTracer();

    void execLineTraceConduct();
    void callLineTraceAct();
    void execLineEdgeTrace();
    void execLineSearch();

private:

};

#endif  // MAINAPP_LINETRACER_OHS_H_
