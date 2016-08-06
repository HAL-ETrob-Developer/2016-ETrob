/* by ohs50465 T.Ueno */

#ifndef MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_

#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "BodyStateAdmin_ohs.h"

typedef struct {
  SCHR event_condition;         //達成条件イベント
  int32_t flow_transition;      //遷移要件
  UCHR action_number;           //実行動作番号
}STATE_FLOW_INDEX;

class ScenarioConductor_ohs {
public:
    //生成
    ScenarioConductor_ohs();
    //デストラクタ
        ~ScenarioConductor_ohs();

    BOOL execScenario();        //シナリオ実行
    void quitCommand();         //指揮終了
    SCHR setScenario();         //シナリオセット
    void setScenarioUpDate();   //シナリオ更新

    //メンバ
    SENC_CLR    mColorSensorState;
    GYRO_STATE  mBalanceState;
    int32_t     mMilage;
    int32_t     mBodyAngle;
    int32_t     mTailAngle;

private:
  //メンバ
  LineTracer_ohs* mLineTracer;
  BodyStateAdmin_ohs* mBodyStateAdmin;
  STATE_FLOW_INDEX　mIndex;

};

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
