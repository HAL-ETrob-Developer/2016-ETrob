/* by ohs50465 T.Ueno */

#ifndef MAINAPP_SCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_SCENARIOCONDUCTOR_OHS_H_

#include "EvStateAdmin_ohs.h"
#include "LineTracer_ohs.h"
#include "PatternSequencer_ohs.h"
// #include "TrackCompass_ohs.h"

//シナリオインデックス関連
#define SCENARIO_MAX_NUM_R  (   _SCENARIO_MAX_NUM_R )
#define SCENARIO_MAX_NUM_L  (   _SCENARIO_MAX_NUM_L )
#define SCENARIO_MAX_NUM    (  101 )/* 右コース+左コース+開始状態 */
#define INIT_SCENARIO_ID    (  100 )/* 開始状態はindex末尾に */
#define SCENARIO_CPY_SIZE   ( sizeof( SCENE_INDEX ) * 100 )/* シナリオインデックスコピーサイズ */
#define LINETRACER_NORMAL   ( _PATTERN_NUM )
#define LINETRACER_SPEED    ( _PATTERN_NUM + 1 )
#define TRACKCOMPASS_CHECK  ( _PATTERN_NUM + 2 )
#define TRACKCOMPASS_ACT    ( _PATTERN_NUM + 3 )

//許容誤差
// #define RUN_MLG_PERMISSION (   50 )
// #define EV3_DEG_PERMISSION (   50 )
#define TIL_DEG_PERMISSION (    2 )

//達成条件:enum化するとEV3RT_2016_FORMと連携取り辛いので
#define CLS_BLK    ( _CLS_BLK )
#define CLS_GRY    ( _CLS_GRY )
#define CLS_WHT    ( _CLS_WHT )
#define RUN_MLG    ( _RUN_MLG )
#define EV3_DEG    ( _EV3_DEG )
#define TIL_DEG    ( _TIL_DEG )
#define GYR__ST    ( _GYR__ST )
#define GYR_UST    ( _GYR_UST )
#define EX_SLIP    ( _EX_SLIP )
#define EX_END     ( _EX_END  )
#define CLS_LIN    ( _CLS_LIN )
#define EX_JUMP    ( _EX_JUMP )
#define RAXIS_T    ( _RAXIS_T )
#define EVENT_NUM  ( _EVENT_NUM )

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
    bool checkJump();
    bool checkRAxisTurn();

    //メンバ
    EvStateAdmin_ohs* mEvStateAdmin;
    LineTracer_ohs* mLineTracer;
    PatternSequencer_ohs* mPatternSequencer;
    // TrackCompass_ohs* mTrackCompass;

    UCHR    mScenarioID;
    SCENE_INDEX mScenario[SCENARIO_MAX_NUM];
    bool ( ScenarioConductor_ohs::*mCheckMethod[EVENT_NUM] )( void );
};

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
