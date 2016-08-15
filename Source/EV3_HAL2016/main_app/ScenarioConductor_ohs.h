/* by ohs50465 T.Ueno */

#ifndef MAINAPP_SCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_SCENARIOCONDUCTOR_OHS_H_

#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "BodyStateAdmin_ohs.h"

<<<<<<< HEAD
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



struct mIndex {
  SCHR event_condition      = NO_CLEAR;   //達成条件
  int32_t flow_transition   = TRACE;      //次の遷移番号
  UCHR action_number        = LINE_TRACE; //実行動作番号
}
=======
#define SCENARIO_MAX_NUM_R  (   50 )
#define SCENARIO_MAX_NUM_L  (   50 )
#define SCENARIO_MAX_NUM    (  101 )//右コース+左コース+開始状態
#define INIT_SCENARIO_ID    (  100 )//開始状態はindex末尾に

//達成条件:enum化するとEV3RT_2016_FORMと連携取り辛いので
#define CLS_BLK    (     0 )
#define CLS_GRY    (     1 )
#define CLS_WHT    (     2 )
#define RUN_MLG    (     3 )
#define EV3_DEG    (     4 )
#define TIL_DEG    (     5 )
#define GYR__ST    (     6 )
#define GYR_UST    (     7 )
#define EX_SLIP    (     8 )
#define EX_END     (     9 )
#define EVENT_NUM  (    10 )

typedef struct _SCENARIO_INDEX {
    UCHR move_event;   //達成条件
    UCHR next_scene;   //次の遷移番号
    UCHR pattern_id;   //実行動作番号
    UCHR dummy;        //バウンダリ対策
    SLNG event_value;  //達成条件に付随する値
}SCENE_INDEX;
>>>>>>> fa7f2176a8d229e984b1e244e7356a4d15e0aa5a

class ScenarioConductor_ohs {
public:
//生成
    ScenarioConductor_ohs( BodyStateAdmin_ohs* body_state_admin, LineTracer_ohs* line_tracer, PatternSequencer_ohs* pattern_sequencer );
    //デストラクタ
    ~ScenarioConductor_ohs();

    BOOL execScenario();                      //シナリオ実行
    void quitCommand();                       //指揮終了
    SCHR setScenario( UCHR uc_scen_no );        //シナリオセット
    void setScenarioUpDate();                 //シナリオ更新

    void setScenarioIndex( SCENE_INDEX* p_scenx_index );//シナリオインデックスの外部登録

private:
    //メンバ
    LineTracer_ohs*       mLineTracer;
    BodyStateAdmin_ohs*   mBodyStateAdmin;
    PatternSequencer_ohs* mPatternSequencer

    UCHR    mScenarioID;
    SCENE_INDEX mScenario[SCENARIO_MAX_NUM];
    void ( *mCheckMethod[EVENT_NUM] )( void );

    void checkRayRef();
    void checkMileage();
    void checkAngle();
    void checkTailDeg();
    void checkGyro();
    void checkQuit();
    void checkSlip();

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
