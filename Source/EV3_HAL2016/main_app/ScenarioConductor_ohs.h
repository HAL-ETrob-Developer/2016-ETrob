/* ---------------------------------------------------------------------------------------------- */
// ScenarioConductor_ohs.h
// EV3_HAL2016\基本機能\シナリオ指揮者
// 競技内容を突破するシナリオを元に、「EvStateAdmin_ohs」「LineTracer_ohs」「PatternSequencer_ohs」
// 「TrackCompass_ohs」に適切な指示を行う。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// SC0000  2016/08/06  上野　徹    新規作成
// SC0001  2016/08/15  大塚　信晶  修正
// SC0002  2016/08/16  大塚　信晶  関数ポインタ記述
// SC0003  2016/08/20  大塚　信晶  設定ファイル取り込み対応化
// SC0004  2016/09/13  大塚　信晶  シナリオ遷移条件の追加「CLS_LIN」
// SC0005  2016/09/15  大塚　信晶  シナリオ遷移条件の追加「EX_JUMP」「RAXIS_T」
/* ---------------------------------------------------------------------------------------------- */
#ifndef MAINAPP_SCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_SCENARIOCONDUCTOR_OHS_H_

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include "EvStateAdmin_ohs.h"
#include "LineTracer_ohs.h"
#include "PatternSequencer_ohs.h"
#include "TrackCompass_ohs.h"

/* ---------------------------------------------------------------------------------------------- */
// 定数定義
/* ---------------------------------------------------------------------------------------------- */

// シナリオインデックス関連
#define SCENARIO_MAX_NUM_R  ( _SCENARIO_MAX_NUM_R )/* シナリオ右コース数 */
#define SCENARIO_MAX_NUM_L  ( _SCENARIO_MAX_NUM_L )/* シナリオ左コース数 */
#define SCENARIO_MAX_NUM    (              101 )   /* 右コース+左コース+開始状態 */
#define INIT_SCENARIO_ID    (              100 )   /* 開始状態はindex末尾に */
#define SCENARIO_CPY_SIZE   ( sizeof( SCENE_INDEX ) * 100 )/* シナリオインデックスコピーサイズ */
// 動作指示番号
#define LINETRACER_NORMAL   ( _PATTERN_NUM     )/* ライントレース低速高精度 */
#define LINETRACER_SPEED    ( _PATTERN_NUM + 1 )/* ライントレース高速低制度 */
#define TRACKCOMPASS_CHECK  ( _PATTERN_NUM + 2 )/* TrackCompass_ohsに基軸決定を指示する */
#define TRACKCOMPASS_TRUN   ( _PATTERN_NUM + 3 )/* 基軸からの旋回指定 */
#define TRACKCOMPASS_MOVEB  ( _PATTERN_NUM + 4 )/* 基軸からの前後進指示＠バランス有り */
#define TRACKCOMPASS_MOVE   ( _PATTERN_NUM + 5 )/* 基軸からの前後進指示＠バランス無し */

//許容誤差
#define TIL_DEG_PERMISSION    (        2 )/* 尻尾指定角度達成許容誤差 */
// #define RUN_MLG_PERMISSION    (       50 )/* 走行指定角度達成許容誤差 */
// #define EV3_DEG_PERMISSION    (       50 )/* 旋回指定角度達成許容誤差 */

//達成条件:enum化するとEV3RT_2016_FORMと連携取り辛いので
#define CLS_BLK    ( _CLS_BLK )/* 達成条件＠黒検知 */
#define CLS_GRY    ( _CLS_GRY )/* 達成条件＠灰検知 */
#define CLS_WHT    ( _CLS_WHT )/* 達成条件＠白検知 */
#define RUN_MLG    ( _RUN_MLG )/* 達成条件＠走行距離 */
#define EV3_DEG    ( _EV3_DEG )/* 達成条件＠旋回角度 */
#define TIL_DEG    ( _TIL_DEG )/* 達成条件＠尻尾角度 */
#define GYR__ST    ( _GYR__ST )/* 達成条件＠ジャイロ安定状態 */
#define GYR_UST    ( _GYR_UST )/* 達成条件＠ジャイロ不安定状態 */
#define EX_SLIP    ( _EX_SLIP )/* 達成条件＠シナリオ移行を行わない */
#define EX_END     ( _EX_END  )/* 達成条件＠システム終了 */
#define CLS_LIN    ( _CLS_LIN )/* 達成条件＠ライン検知（白以外を検知） */
#define EX_JUMP    ( _EX_JUMP )/* 達成条件＠強制達成 */
#define RAXIS_T    ( _RAXIS_T )/* 達成条件＠基軸旋回達成 */
#define EVENT_NUM  ( _EVENT_NUM )/* 達成条件個数 */

/* ---------------------------------------------------------------------------------------------- */
// クラス名     : ScenarioConductor_ohs
// 役割名       : シナリオコンダクター
// 役割概要     : 競技突破の為に構成されたシナリオに従い状態遷移を管理する。
// 作成日       : 2016/08/06  上野　徹    新規作成
//                2016/08/15  大塚　信晶  修正
/* ---------------------------------------------------------------------------------------------- */
class ScenarioConductor_ohs {
    public:/* ------------------------------------------------------------------------ パブリック */
        // コンストラクタ
        ScenarioConductor_ohs( EvStateAdmin_ohs* ev_state_admin, LineTracer_ohs* line_tracer, PatternSequencer_ohs* pettern_sequencer, TrackCompass_ohs* track_compass );
        // デストラクタ
        ~ScenarioConductor_ohs();

        BOOL execScenario();//シナリオ実行
        void quitCommand(); //指揮終了
        BOOL setScenario( UCHR uc_scen_no );//シナリオセット
        BOOL setScenarioUpDate();//シナリオ更新

        BOOL setScenarioIndex( SCENE_INDEX* p_scenx_index );//シナリオインデックスの外部登録
        UCHR getID();//現行インデックス取得

    private:/* --------------------------------------------------------------------- プライベート */
        /* メソッド＠mCheckMethod登録用 */
        bool checkRayRef();   // 条件達成確認＠光学センサ関連
        bool checkMileage();  // 条件達成確認＠走行量確認
        bool checkAngle();    // 条件達成確認＠旋回角度
        bool checkTailDeg();  // 条件達成確認＠尻尾角度
        bool checkGyro();     // 条件達成確認＠ジャイロ値
        bool checkQuit();     // 条件達成確認＠システム終了
        bool checkSlip();     // 条件達成確認＠シナリオ遷移停止
        bool checkJump();     // 条件達成確認＠シナリオ強制遷移
        bool checkRAxisTurn();// 条件達成確認＠基軸旋回確認

        /* メンバ */
        EvStateAdmin_ohs* mEvStateAdmin;// 本体状態管理
        LineTracer_ohs* mLineTracer;    // ライントレーサ
        PatternSequencer_ohs* mPatternSequencer;//定量走行者 
        TrackCompass_ohs* mTrackCompass;// コース基軸管理

        UCHR mScenarioID;// 現行シナリオID
        SCENE_INDEX mScenario[SCENARIO_MAX_NUM];// シナリオ構成記録
        // シナリオ移行条件確認メソッド配列
        bool ( ScenarioConductor_ohs::*mCheckMethod[EVENT_NUM] )( void );

};// class ScenarioConductor_ohs

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
