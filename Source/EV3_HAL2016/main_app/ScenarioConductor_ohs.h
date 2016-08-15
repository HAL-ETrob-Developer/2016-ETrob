/* by ohs50465 T.Ueno */

#ifndef MAINAPP_SCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_SCENARIOCONDUCTOR_OHS_H_

#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"
#include "BodyStateAdmin_ohs.h"

#define SCENARIO_MAX_NUM_R  (   50 )
#define SCENARIO_MAX_NUM_L  (   50 )
#define SCENARIO_MAX_NUM    (  100 )

//達成条件:enum化するとEV3RT_2016_FORMと連携取り辛いので
#define CLS_BLK    (     0 )
#define CLS_GRY    (     1 )
#define CLS_WHT    (     2 )
#define RUN_MLG    (     3 )
#define EV3_DEG    (     4 )
#define TIL_DEG    (     5 )
#define GYRO_ST    (     6 )
#define EX_SLIP    (     7 )
#define EX_END     (     8 )
#define EVENT_NUM  (     9 )

typedef struct _SCENARIO_INDEX {
    UCHR move_event;   //達成条件
    SLNG event_value;  //達成条件に付随する値
    UCHR next_scene;   //次の遷移番号
    UCHR pattern_id;   //実行動作番号
}SCENE_INDEX;

class ScenarioConductor_ohs {
public:
//生成
    ScenarioConductor_ohs( BodyStateAdmin_ohs* body_state_admin, LineTracer_ohs* line_tracer, PatternSequencer_ohs* pattern_sequencer );
    //デストラクタ
    ~ScenarioConductor_ohs();

    BOOL execScenario();                      //シナリオ実行
    void quitCommand();                       //指揮終了
    SCHR setScenario( UCHR ucScenNo );        //シナリオセット
    void setScenarioUpDate();                 //シナリオ更新

private:
    //メンバ
    LineTracer_ohs*       mLineTracer;
    BodyStateAdmin_ohs*   mBodyStateAdmin;
    PatternSequencer_ohs* mPatternSequencer

    int         mIndex;
    SCENE_INDEX mScenario[SCENARIO_MAX_NUM];
    void ( *mCheckMethod[EVENT_NUM] )( void );

    void checkGyro();
    void checkRayRef();
    void checkMileage();
    void checkAngle();
    void checkTailDeg();
    void checkQuit();
    void checkSlip();

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
