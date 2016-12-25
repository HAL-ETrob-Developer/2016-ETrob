/* ---------------------------------------------------------------------------------------------- */
// app.cpp
// EV3_HAL2016\アプリケーション
// ETロボコン2016_HAL基本アプリケーション
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// AP0000  2016/07/12  大塚　信晶  新規作成
// AP0001  2016/07/23  大塚　信晶  ライントレース新機能
// AP0002  2016/08/18  大塚　信晶  全機能の実装の完了
// AP0003  2016/08/20  大塚　信晶  設定ファイル通信機能の追加
// AP0004  2016/08/21  大塚　信晶  試走会1の結果を適用
// AP0005  2016/09/04  大塚　信晶  状態の追加に対する調整
// AP0006  2016/09/04  大塚　信晶  障害物突破に関する設計変更・追加
// AP0007  2016/09/18  大塚　信晶  ジャイロセンサ異常対策
// AP0008  2016/09/18  大塚　信晶  競技前調整
// AP0009  2016/12/18  大塚　信晶  コーディング規約に元づく修正・コメントの付与
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include "ev3api.h"
#include "syssvc/serial.h"
#include "app.h"
#include "balancer.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"

#include "hal_ev3_std.h"

#include "./main_app/LineTracer_ohs.h"
#include "./main_app/PatternSequencer_ohs.h"
#include "./main_app/EvStateAdmin_ohs.h"
#include "./main_app/ScenarioConductor_ohs.h"
#include "./main_app/TrackCompass_ohs.h"

#include "./calculation/RunLineCalculator_ohs.h"
#include "./calculation/Balancer_ohs.h"

#include "./device_ope/RunningAdmin_ohs.h"
#include "./device_ope/GyroAdmin_ohs.h"
#include "./device_ope/RayReflectAdmin_ohs.h"
#include "./device_ope/TailAdmin_ohs.h"

/* ---------------------------------------------------------------------------------------------- */
// using宣言
/* ---------------------------------------------------------------------------------------------- */

using namespace ev3api;

/* ---------------------------------------------------------------------------------------------- */
// 定数定義
/* ---------------------------------------------------------------------------------------------- */

/* コンパイラに依存する記述 --------------------------------------------------------------------- */
#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetoothコマンド ---------------------------------------------------------------------------- */
#define CMD_RIGHIT (      'r' )/* リモートスタートコマンド */
#define RIGHIT_ID  (        0 )/* シナリオ指定ID */
#define CMD_LEFT   (      'l' )/* リモートスタートコマンド */
#define LEFT_ID    (       50 )/* シナリオ指定ID */
/* コマンド（シナリオNo） */
#define SCENE_Q    (       45 )
#define SCENE_W    (       46 )
#define SCENE_E    (       47 )
#define SCENE_R    (       48 )
#define SCENE_T    (       49 )
#define SCENE_Y    (       95 )
#define SCENE_U    (       96 )
#define SCENE_I    (       97 )
#define SCENE_O    (       98 )
#define SCENE_P    (       99 )
#define SCENE_Z    (      100 )
#define SCENE_X    (       93 )

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* ジャイロセンサ異常対策 ----------------------------------------------------------------------- */
//概要:
//関数ポインター配列にダミーのメソッドと、ジャイロセンサアクセスを行う実際のメソッドを格納し、
//その関数ポインター配列の添え字の入れ替えでジャイロセンサの動作の切り替えを行う
//（if文によるフラグ式にしないのは、クリティカル領域にif文入れたくないからです）
//void ( GyroAdmin_ohs::*gGyroValueUpdate[GYRO_M_ID_NUM] )( void )
/* ---------------------------------------------------------------------------------------------- */
#define GYRO_OFF        (0)    /* ジャイロセンサの動作OFF */
#define GYRO_ON         (1)    /* ジャイロセンサの動作ON */
#define GYRO_M_ID_NUM   (2)    /* callValueUpdate1メソッド格納用 */

/* ---------------------------------------------------------------------------------------------- */
// グローバル変数宣言
/* ---------------------------------------------------------------------------------------------- */

/* ジャイロセンサ異常対策 */
static int gGyroSwitch = GYRO_OFF;/* ジャイロセンサの動作スイッチ */

/* Bluetooth */
static UCHR  bt_cmd = '0';// Bluetoothコマンド
// static FILE* gBtHandle = NULL;      /* Bluetoothファイルハンドル */
FILE* gBtHandle = NULL;// Bluetoothファイルハンドル＠外部で使うことあるのでstatic取りました

/* オブジェクトへのポインタ定義＠ev3api */
TouchSensor*    touchSensor;// 不使用
SonarSensor*    sonarSensor;// 不使用
ColorSensor*    colorSensor;
GyroSensor*     gyroSensor;
Motor*          leftMotor;
Motor*          rightMotor;
Motor*          tailMotor;
Clock*          clock;// 不使用

/* オブジェクトへのポインタ定義＠ev3hal_2016 */
static PatternSequencer_ohs*   gPatternSequencer;
static EvStateAdmin_ohs*       gEvStateAdmin;
static ScenarioConductor_ohs*  gScenarioConductor;
static LineTracer_ohs*         gLineTracer;
static RunLineCalculator_ohs*  gRunLineCalculator;
static RayReflectAdmin_ohs*    gRayReflectAdmin;
static Balancer_ohs*           gBalancer;
static RunningAdmin_ohs*       gRunningAdmin;
static GyroAdmin_ohs*          gGyroAdmin;
static TailAdmin_ohs*          gTailAdmin;
static TrackCompass_ohs*       gTrackCompass;
void ( GyroAdmin_ohs::*gGyroValueUpdate[GYRO_M_ID_NUM] )( void );//ジャイロセンサ更新メソッド格納用

/* ---------------------------------------------------------------------------------------------- */
// プロトタイプ宣言
/* ---------------------------------------------------------------------------------------------- */

static void user_system_create( void );// コンストラクタを一括処理
static void user_system_destroy( void );// デストラクタを一括処理
static bool SetingFileload( char* f_pass, memfile_t* ev3_file_stc );//SDカード->オブジェクト
static bool SetingFileWrite( char* f_pass, FILE* bt_handle );//BT->SDカード

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : main_task
// 機能名   : メインタスク
// 機能概要 : 一番最初に起動するタスク、全タスク・オブジェクトの生成・削除を行う。
// 作成日   : 2016/07/12  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]intptr_t unused : 割り込みフラグ＠未使用
/* ---------------------------------------------------------------------------------------------- */
void main_task(intptr_t unused)
{
    ev3_led_set_color(LED_OFF);// 起動確認用＠本体正面LED_OFF

    user_system_create();  // オブジェクトの生成

    ev3_led_set_color(LED_GREEN);// 起動確認用＠本体正面LED_緑点灯

    /* 周期ハンドラ開始 */
    ev3_sta_cyc(EV3_CYC_TRACER);

    /* Bluetooth通信タスクの起動 */
    act_tsk(BT_TASK);

    /* 基本動作タスクの開始 */
    act_tsk(TRACER_TASK);

    slp_tsk();// wup_tsk()が指示されるまで以降の処理を保留する

    /* 周期ハンドラ停止 */
    ev3_stp_cyc(EV3_CYC_TRACER);
    /* Bluetooth通信タスクの破棄 */
    ter_tsk(BT_TASK);
    /* 基本動作タスクの破棄 */
    ter_tsk(TRACER_TASK);
    /* 終了処理 */
    user_system_destroy();

    ext_tsk();// タスク終了
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : user_system_create
// 機能名   : オブジェクト生成
// 機能概要 : 全オブジェクトの初期化、グローバル変数の初期化、保存設定ファイルの取り込みを行う
// 作成日   : 2016/07/12  大塚　信晶  新規作成
/* ---------------------------------------------------------------------------------------------- */
static void user_system_create( void )
{
    memfile_t PidSetStract;// 設定ファイル
    memset( &PidSetStract, 0,sizeof( PidSetStract ));

    /* 各オブジェクトを生成・初期化する */
    touchSensor = new TouchSensor(PORT_1);
    colorSensor = new ColorSensor(PORT_3);
    //sonarSensor = new SonarSensor(PORT_2);// コード抜いた状態でこれ入れるとここで止まります
    gyroSensor  = new GyroSensor(PORT_4);
    leftMotor   = new Motor(PORT_C);
    rightMotor  = new Motor(PORT_B);
    tailMotor   = new Motor(PORT_A);
    clock       = new Clock();

    gRunLineCalculator = new RunLineCalculator_ohs();
    gTailAdmin = new TailAdmin_ohs( *tailMotor );
    gGyroAdmin = new GyroAdmin_ohs( *gyroSensor );
    gBalancer  = new Balancer_ohs( gGyroAdmin );
    gRunningAdmin = new RunningAdmin_ohs( *leftMotor, *rightMotor, gBalancer );
    gRayReflectAdmin = new RayReflectAdmin_ohs( *colorSensor );

    gTrackCompass = new TrackCompass_ohs( gRunningAdmin, gRunLineCalculator );
    gEvStateAdmin = new EvStateAdmin_ohs( gRayReflectAdmin, gGyroAdmin, gRunningAdmin, gTailAdmin );
    gLineTracer   = new LineTracer_ohs( gRunningAdmin, gRayReflectAdmin, gRunLineCalculator );
    gPatternSequencer  = new PatternSequencer_ohs( gRunningAdmin, gTailAdmin );
    gScenarioConductor = new ScenarioConductor_ohs( gEvStateAdmin, gLineTracer, gPatternSequencer, gTrackCompass );

    /* ジャイロセンサ異常対策＠関数ポインターの登録 */
    gGyroValueUpdate[GYRO_OFF] = &GyroAdmin_ohs::callValueUpdateDummy;
    gGyroValueUpdate[GYRO_ON]  = &GyroAdmin_ohs::callValueUpdate;

    /* Bluetooth＠ハンドラの取得 */
    gBtHandle = ev3_serial_open_file( EV3_SERIAL_BT );
    assert( gBtHandle != NULL );

    /* 設定ファイルの取得 */
    SetingFileload(( char* )PID_SET_FILE_PASS, &PidSetStract );
    ev3_memfile_free( &PidSetStract );

    fprintf( gBtHandle,"[system_create]\r\n");// システム起動完了を通知する

    return;
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : user_system_destroy
// 機能名   : オブジェクト削除
// 機能概要 : 生成した全オブジェクトを削除する
// 作成日   : 2016/07/12  大塚　信晶  新規作成
/* ---------------------------------------------------------------------------------------------- */
static void user_system_destroy( void )
{
    if( gRunLineCalculator ) { delete gRunLineCalculator; gRunLineCalculator = NULL; }
    if( gTailAdmin         ) { delete gTailAdmin;         gTailAdmin         = NULL; }
    if( gRayReflectAdmin   ) { delete gRayReflectAdmin;   gRayReflectAdmin   = NULL; }
    if( gRunningAdmin      ) { delete gRunningAdmin;      gRunningAdmin      = NULL; }
    if( gGyroAdmin         ) { delete gGyroAdmin;         gGyroAdmin         = NULL; }
    if( gBalancer          ) { delete gBalancer;          gBalancer          = NULL; }
    if( gLineTracer        ) { delete gLineTracer;        gLineTracer        = NULL; }
    if( gEvStateAdmin      ) { delete gEvStateAdmin;      gEvStateAdmin      = NULL; }
    if( gPatternSequencer  ) { delete gPatternSequencer;  gPatternSequencer  = NULL; }
    if( gScenarioConductor ) { delete gScenarioConductor; gScenarioConductor = NULL; }
    if( gTrackCompass      ) { delete gTrackCompass;      gTrackCompass      = NULL; }

    if( touchSensor        ) { delete touchSensor;        touchSensor        = NULL; }
    if( colorSensor        ) { delete colorSensor;        colorSensor        = NULL; }
    if( sonarSensor        ) { delete sonarSensor;        sonarSensor        = NULL; }
    if( gyroSensor         ) { delete gyroSensor;         gyroSensor         = NULL; }
    if( leftMotor          ) { delete leftMotor;          leftMotor          = NULL; }
    if( rightMotor         ) { delete rightMotor;         rightMotor         = NULL; }
    if( tailMotor          ) { delete tailMotor;          tailMotor          = NULL; }
    if( clock              ) { delete clock;              clock              = NULL; }

    if( gBtHandle != NULL )  { fclose(gBtHandle); }

    return;
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : ev3_cyc_tracer
// 機能名   : 競技用割り込みタスクバイパス
// 機能概要 : 指定した割り込み周期で起動する。割り込みタスクは優先度を指定できない為、
//            別途優先度指定したタスクを起動するバイパスの役割を持つ
// 作成日   : 2016/07/12  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]intptr_t exinf : 割り込みフラグ＠未使用
/* ---------------------------------------------------------------------------------------------- */
void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(INTERRUPT_TASK);
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : interrupt_task
// 機能名   : 競技用割り込みタスク
// 機能概要 : 各デバイスの操作と一定周期的に行われるべきフィードバック計算を行う
// 作成日   : 2016/07/12  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]intptr_t exinf : 割り込みフラグ＠未使用
/* ---------------------------------------------------------------------------------------------- */
void interrupt_task(intptr_t exinf) {
    //センシング
    // gGyroAdmin->callValueUpdate();//ジャイロセンサ異常対策＠20160918
    ( gGyroAdmin->*gGyroValueUpdate[gGyroSwitch] )();//ジャイロセンサ異常対策＠20160918
    gRunningAdmin->callValueUpDate();
    gRayReflectAdmin->callValueUpDate();
    gTailAdmin->callValueUpDate();

    //制御
    gLineTracer->callLineTraceAct();
    ////gLineTracer->callSimplLineTraceAct();
    gTrackCompass->callReferenceSearch();

    //アクチュエイト
    gRunningAdmin->callRunning();
    gTailAdmin->callActDegree();

#ifdef INTERRUPT_CHK /* 割り込みが周期的に行われているかを確認する為 */
    static int tes = 0;
    tes++;
    if( tes > 100 ) {
        ev3_speaker_play_tone( NOTE_AS5, 10 );
        ev3_led_set_color(LED_RED);
        tes = 0;
    } else if( tes == 50 ) {
        ev3_led_set_color(LED_GREEN);
    }
#endif

    ext_tsk();// タスク終了
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : tracer_task
// 機能名   : トレーサータスク
// 機能概要 : 本体のメインループ
// 作成日   : 2016/07/12  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]intptr_t exinf : 割り込みフラグ＠未使用
/* ---------------------------------------------------------------------------------------------- */
void tracer_task(intptr_t exinf) {
    bool sceneGo = true;// シナリオ進行フラグ

    /* メインループ ----------------------------------------------------------------------------- */
    while( ev3_button_is_pressed( BACK_BUTTON ) == false ) {

        sceneGo = gScenarioConductor->execScenario();//メイン処理

        if( sceneGo == false ) { break; }// シナリオ終了
        if( ev3_button_is_pressed(BACK_BUTTON)) { break; }// バックボタン押込みで強制終了

    }// バックボタン押込みで強制終了＠多分whileの条件文は消し忘れです

    ev3_led_set_color(LED_RED);// シナリオ終了表示

    gScenarioConductor->quitCommand();// シナリオ終了操作

    // clock->sleep(500);// 終了待機（前コードの名残ですがclockの使い方の参考においときます）

    wup_tsk(MAIN_TASK);// メインタスクのslp_tsk()を解除する
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : bt_task
// 機能名   : Bluetoothタスク
// 機能概要 : Bluetooth通信を行う
// 作成日   : 2016/07/12  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]intptr_t unused : 割り込みフラグ＠未使用
/* ---------------------------------------------------------------------------------------------- */
void bt_task(intptr_t unused)
{
    int32_t lTilOfset = 0; // 尻尾オフセット＠イニシャライズ用
    memfile_t PidSetStract;// パラメータ設定ファイル
    SCHR bt_cmd_ = 0;      // 受信Bluetoothコマンド一次受け

    memset( &PidSetStract, 0,sizeof( PidSetStract ));// 設定ファイル格納領域の初期化

    Bluetooth受信待ちループ
    while( true )
    {
#ifdef SOUND_ANSWER
        ev3_speaker_play_tone( NOTE_C4, 80 );// 受信アンサー音
#endif

        bt_cmd_ = fgetc(gBtHandle); /* 受信 */
        bt_cmd = bt_cmd_;// グローバル領域へ移動

        // serial_rea_dat(SIO_PORT_BT, (char*)&bt_cmd, 1);// Bluetooth受信の別手段です。参考に

        /* -------------------------------------------------------------------------------------- */
        // コマンド処理
        // 競技に不要なコマンドはコメントアウトしています＠AP0008 2016/09/18 大塚　信晶 競技前調整
        /* -------------------------------------------------------------------------------------- */
        switch( bt_cmd ) {
            case CMD_RIGHIT://右コースセット
                gGyroSwitch = GYRO_ON;
                gScenarioConductor->setScenario( RIGHIT_ID );
                break;
            case CMD_LEFT://左コース
                gGyroSwitch = GYRO_ON;
                gScenarioConductor->setScenario( LEFT_ID );
                break;
            case 'S'://ファイル読み込み
                SetingFileWrite(( char* )PID_SET_FILE_PASS, gBtHandle );
                SetingFileload(( char* )PID_SET_FILE_PASS, &PidSetStract );
                ev3_memfile_free( &PidSetStract );
                break;
            case 'B'://Bluetooth通信の終了
                goto EXIT;
                break;
            case 'X':
                gScenarioConductor->setScenario( SCENE_X );
                break;
            case 'z':
                gGyroSwitch = GYRO_OFF;
                gScenarioConductor->setScenario( SCENE_Z );
                break;
            // case 'h':
            //     ev3_stp_cyc(EV3_CYC_TRACER);
            //     gGyroAdmin->callValueUpdate();//stop
            //     ev3_sta_cyc(EV3_CYC_TRACER);
                
            //     break;

            case 'q':
                gGyroSwitch = GYRO_ON;
                gScenarioConductor->setScenario( SCENE_Q );
                break;
            case 'w':
                gGyroSwitch = GYRO_OFF;
                gScenarioConductor->setScenario( SCENE_Q );
                break;
            // case 'q':
            //     gScenarioConductor->setScenario( SCENE_Q );
            //     break;
            // case 'w':
            //     gScenarioConductor->setScenario( SCENE_W );
            //     break;
            // case 'e':
            //     gScenarioConductor->setScenario( SCENE_E );
            //     break;
            // case 'r':
            //     gScenarioConductor->setScenario( SCENE_R );
            //     break;
            // case 't':
            //     gScenarioConductor->setScenario( SCENE_T );
            //     break;
            // case 'y':
            //     gScenarioConductor->setScenario( SCENE_Y );
            //     break;
            // case 'u':
            //     gScenarioConductor->setScenario( SCENE_U );
            //     break;
            // case 'i':
            //     gScenarioConductor->setScenario( SCENE_I );
            //     break;
            case 'o':
                gGyroSwitch = GYRO_OFF;
                gScenarioConductor->setScenario( SCENE_O );
                break;
            // case 'p':
            //     gScenarioConductor->setScenario( SCENE_P );
            //     break;
            case '<':
                lTilOfset++;
                fprintf( gBtHandle,"<%d>\r\n", (int)lTilOfset );
                gTailAdmin->setOfsetDegree( lTilOfset );
                break;
            case '>':
                lTilOfset--;
                fprintf( gBtHandle,"<%d>\r\n", (int)lTilOfset );
                gTailAdmin->setOfsetDegree( lTilOfset );
                break;
            default:
                break;
        }
        /* -------------------------------------------------------------------------------------- */
        // Bluetooth返信＠テスト状況でその時々に必要なの出力してます
        /* -------------------------------------------------------------------------------------- */
        fprintf( gBtHandle,"[%c]\r\n", bt_cmd );

        fprintf( gBtHandle,"Scenario[%3d]\r\n",gScenarioConductor->getID());
        fprintf( gBtHandle,"Pattern [%3d]\r\n",gPatternSequencer->getID());
        fprintf( gBtHandle,"Mileage [%d]\r\n",(int)gEvStateAdmin->getMileage());
        fprintf( gBtHandle,"Angle   [%d]\r\n",(int)gEvStateAdmin->getBodyAngle());
        fprintf( gBtHandle,"TailDeg [%d]\r\n",(int)gEvStateAdmin->getTailAngle());
        fprintf( gBtHandle,"Color   [%d]\r\n",(int)gEvStateAdmin->getColorSensorState());
        fprintf( gBtHandle,"Balance [%d]\r\n",(int)gEvStateAdmin->getBalanceState());
        // fprintf( gBtHandle,"Mileage [%d]\r\n",(int)gRunningAdmin->getMileage());
        // fprintf( gBtHandle,"Degree  [%d]\r\n",(int)gRunningAdmin->getAngle());
        fprintf( gBtHandle,"Battery [%d]\r\n",(int)ev3_battery_voltage_mV());
        
        bt_cmd = 0;//リセット
    }

EXIT:/* Bluetooth通信の終了 */
    fprintf( gBtHandle,"See you !\r\n");
#ifdef SOUND_ANSWER
    ev3_speaker_play_tone( NOTE_C4, 240 );
#endif
    return;
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : SetingFileload
// 機能名   : 設定ファイル読込
// 機能概要 : SDカード上に保存された設定ファイルを各オブジェクトに適応します。
// 適応範囲 : gRunLineCalculator >>> PID制御ゲイン値・目標光学値・目標走行速度
//          : gPatternSequencer  >>> 動作パターン
//          : gScenarioConductor >>> シナリオ
// 作成日   : 2016/08/20  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]char*      f_pass       : ファイル保存先SDカードパス
// [OUT]memfile_t* ev3_file_stc : SDカードデータ取得用メモリ
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true :正常終了
// false:異常終了
/* ---------------------------------------------------------------------------------------------- */
static bool SetingFileload( char* f_pass, memfile_t* ev3_file_stc )
{
    /* ファイル構造体の生成 */
    EV3_SETTING  strcEv3File;
    ER ret;
    memset( &strcEv3File, 0, sizeof(EV3_SETTING));

    /* 異常終了 : ぬるぽ */
    if( f_pass == NULL ) { return false; }
    if( ev3_file_stc == NULL ) { return false; }

    /* メモリ上にすでにファイルあれば削除 */
    if( ev3_file_stc->buffer != NULL ) {
        ev3_memfile_free( ev3_file_stc );
    }

    /* SDカードから設定ファイルを取り込み */
    ret = ev3_memfile_load( f_pass, ev3_file_stc );
    assert( ret != E_OK );

    /* 異常終了:ファイルサイズが異常 */
    if( ev3_file_stc->buffersz != sizeof(EV3_SETTING) ) { return false; }

    /* メモリ領域から構造体へ変換 */
    memcpy( &strcEv3File, ev3_file_stc->buffer,sizeof(EV3_SETTING));

    /* 設定ファイルのロード＠パラメタ変更 */
    gRunLineCalculator->setGain( &strcEv3File.nmPidSetting );
    gPatternSequencer->setPatternIndex( &strcEv3File.patrnIndexS[0] );
    gScenarioConductor->setScenarioIndex( &strcEv3File.sceneIndexS[0] );

    /* 読み込みの正常終了確認用＠BTで文字化けしたデータ飛んでないか見るやつです ----------------- */
    PID_SETTING* test;
    test = gRunLineCalculator->isGain();
    fprintf( gBtHandle,"nm[%f][%f]sc[%f][%f]\r\n",
        ( test + 0 )->fTerSpeed,( test + 0 )->fTerRefLv, 
        ( test + 1 )->fTerSpeed,( test + 1 )->fTerRefLv );
    /* 読み込みの正常終了確認用＠ここまで ------------------------------------------------------- */

    return true;// 正常終了
}

/* ---------------------------------------------------------------------------------------------- */
// 関数名   : SetingFileWrite
// 機能名   : 設定ファイル取得保存
// 機能概要 : Bluetooth通信で設定ファイルを取得し、SDカードへ保存します。
// 作成日   : 2016/08/20  大塚　信晶  新規作成
/* ---------------------------------------------------------------------------------------------- */
static bool SetingFileWrite( char* f_pass, FILE* bt_handle )
{
    FILE* SDFileH = NULL;// SDカードへのハンドラ
    /* ファイル構造体の生成（一時受け用） */
    int8_t  cDummy[sizeof(EV3_SETTING)];
    memset( &cDummy[0], 0, 100);// 初期化

    /* 異常終了 : ぬるぽ */
    if( f_pass == NULL ) { return false; }
    if( bt_handle == NULL ) { return false; }

    /* ユーザーレスポンス */
    fprintf( gBtHandle,"----FILE IN----\r\n" ); /* エコーバック＠BT */
#ifdef SOUND_ANSWER
    ev3_speaker_play_tone( NOTE_C4, 500 );// 音
#endif
    /* Bt受付 */
    fread( cDummy, sizeof(char), sizeof(EV3_SETTING), bt_handle );

    /* ユーザーレスポンス */
    fprintf( gBtHandle,"--FILE COMMIT--\r\n" ); /* エコーバック＠BT */
#ifdef SOUND_ANSWER
    ev3_speaker_play_tone( NOTE_C4, 500 );// 音
#endif

    /* 一時受けからSDカードへ書き込み */
    SDFileH = fopen( f_pass, "wb" );//ファイルオープン＠バイナリモード上書き

    if( SDFileH != NULL ) {
        fwrite( cDummy, sizeof(char), sizeof(cDummy), SDFileH );//書き込み
        fclose( SDFileH );//SDファイルクローズ
    } else {
        return false;// ヌルポ終了
    }

    return true;// 正常終了
}
