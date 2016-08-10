/* by ohs50465 T.Ueno */

#ifndef MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_

#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "BodyStateAdmin_ohs.h"

/* 達成条件 */
#define TRACE_CLEAR     (    1  )
#define HURDLE1_CLEAR   (    2  )
#define HURDLE2_CLEAR   (    3  )

/* 次の遷移番号 */
#define TRACE           (    0  )
#define HURDLE1         (    1  )
#define HURDLE2         (    2  )

/* 実行動作番号 */
#define LINE_TRACE      (   '1' )
#define PETTERN_RUNNING (   '2' )

typedef struct {
  SCHR event_condition      = LINE_TRACE;         //達成条件
  int32_t flow_transition   = TRACE;              //次の遷移番号
  UCHR action_number        = LINE_TRACE;         //実行動作番号
}STATE_FLOW_INDEX;

class ScenarioConductor_ohs {
public:
    //生成
    ScenarioConductor_ohs();
    //デストラクタ
        ~ScenarioConductor_ohs();

    BOOL execScenario();                      //シナリオ実行
    void quitCommand();                       //指揮終了
    SCHR setScenario( RUNNING_ROUTE route );  //シナリオセット
    void setScenarioUpDate();                 //シナリオ更新

    //メンバ
    SENC_CLR    mColorSensorState;
    GYRO_STATE  mBalanceState;
    int32_t     mMilage;
    int32_t     mBodyAngle;
    int32_t     mTailAngle;

    //記録用
    SENC_CLR    ColorSensorState;
    GYRO_STATE  BalanceState;
    int32_t     Milage;
    int32_t     BodyAngle;
    int32_t     TailAngle;

private:
  //メンバ
  LineTracer_ohs*     mLineTracer;
  BodyStateAdmin_ohs* mBodyStateAdmin;
  STATE_FLOW_INDEX    mIndex;
  RUNNING_ROUTE       mRoute;

};

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
