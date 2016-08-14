/* by ohs50465 T.Ueno */

#ifndef MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_

#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "BodyStateAdmin_ohs.h"

/* 達成条件 */
#define NO_CLEAR        (    0  ) //ゴールしていない
#define TRACE_CLEAR     (    1  ) //ゴールした
#define HURDLE1_CLEAR   (    2  ) //難所クリア
#define HURDLE2_CLEAR   (    3  ) //ガレージインクリア

/* 次の遷移番号 */
#define TRACE           (    0  ) //トレース
#define HURDLE1         (    1  ) //難所
#define HURDLE2         (    2  ) //ガレージイン

/* 実行動作番号 */
#define LINE_TRACE      (   '1' ) //ライントレース
#define PETTERN_RUNNING (   '2' ) //定量走行
#define LOOKUP_GATE     (   '3' ) //ルックアップゲート
#define STEP            (   '4' ) //階段



typedef struct {
  SCHR event_condition      = NO_CLEAR;   //達成条件
  int32_t flow_transition   = TRACE;      //次の遷移番号
  UCHR action_number        = LINE_TRACE; //実行動作番号
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

    //目標値を入れる変数
    SINT TargetMilage1   = 0;/* 初期値(スタートからゴールまでの距離) */
    SINT TargetMilage2   = 0;/* 初期値(ゴールから難所通過後のグレーまでの距離) */
    SINT TargetTailAngle = 0;/* 初期値(ルックアップゲートを通過できる角度) */
    SINT TargetMilage3   = 0;/* 初期値(難所通過後のグレーからガレージ内停止位置までの距離) */

private:
  //メンバ
  LineTracer_ohs*     mLineTracer;
  BodyStateAdmin_ohs* mBodyStateAdmin;
  STATE_FLOW_INDEX    mIndex;
  RUNNING_ROUTE       mRoute;

};

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
