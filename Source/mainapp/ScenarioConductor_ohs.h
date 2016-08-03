/* by ohs50465 T.Ueno */

#ifndef MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_

#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "BodyStateAdmin_ohs.h"

typedef struct STATE_FLOW_INDEX {
  SCHR event_condition;         //達成条件イベント
  int32_t flow_transition;      //遷移要件
  UCHR action_number;           //実行動作番号
};

class ScenarioConductor_ohs {
public:
    //生成
    ScenarioConductor_ohs();
    //デストラクタ
        ~ScenarioConductor_ohs();

    BOOL execScenario();        //シナリオ実行
    void quitCommand();         //指揮終了
    SCHR setScenario();         //現・本体状態の記録
    void setScenarioUpDate();   //シナリオ更新

private:

  //メンバ
  LineTracer_ohs* mLineTracer;
};

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
