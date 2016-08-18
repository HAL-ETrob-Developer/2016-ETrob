/* by ohs50465 T.Ueno */

#ifndef MAINAPP_SCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_SCENARIOCONDUCTOR_OHS_H_

#include "EvStateAdmin_ohs.h"
#include "LineTracer_ohs.h"
#include "PatternSequencer_ohs.h"

//シナリオインデックス関連
#define SCENARIO_MAX_NUM_R  (   50 )
#define SCENARIO_MAX_NUM_L  (   50 )
#define SCENARIO_MAX_NUM    (  101 )/* 右コース+左コース+開始状態 */
#define INIT_SCENARIO_ID    (  100 )/* 開始状態はindex末尾に */
#define SCENARIO_CPY_SIZE   ( sizeof( SCENE_INDEX ) * 100 )/* シナリオインデックスコピーサイズ */

//許容誤差
// #define RUN_MLG_PERMISSION (   50 )
// #define EV3_DEG_PERMISSION (   50 )
#define TIL_DEG_PERMISSION (    1 )

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

class ScenarioConductor_ohs {
public:
//生成
    ScenarioConductor_ohs( EvStateAdmin_ohs* ev_state_admin, LineTracer_ohs* line_tracer, PatternSequencer_ohs* pettern_sequencer );
    //デストラクタ
    ~ScenarioConductor_ohs();

    BOOL execScenario();                      //シナリオ実行
    void quitCommand();                       //指揮終了
    BOOL setScenario( UCHR uc_scen_no );        //シナリオセット
    BOOL setScenarioUpDate();                 //シナリオ更新

    BOOL setScenarioIndex( SCENE_INDEX* p_scenx_index );//シナリオインデックスの外部登録
    UCHR getID();//現行インデックス取得

private:

    bool checkRayRef();
    bool checkMileage();
    bool checkAngle();
    bool checkTailDeg();
    bool checkGyro();
    bool checkQuit();
    bool checkSlip();

    //メンバ
    EvStateAdmin_ohs* mEvStateAdmin;
    LineTracer_ohs* mLineTracer;
    PatternSequencer_ohs* mPatternSequencer;

    UCHR    mScenarioID;
    SCENE_INDEX mScenario[SCENARIO_MAX_NUM];
    bool ( ScenarioConductor_ohs::*mCheckMethod[EVENT_NUM] )( void );
};

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
