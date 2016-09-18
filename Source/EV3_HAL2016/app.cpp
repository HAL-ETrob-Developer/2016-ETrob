/**
 ******************************************************************************
 ** ファイル名 : app.cpp
 **
 ** 概要 : 2輪倒立振子ライントレースロボットのTOPPERS/HRP2用C++サンプルプログラム
 **
 ** 注記 : sample_cpp (ライントレース/尻尾モータ/超音波センサ/リモートスタート)
 ******************************************************************************
 **/
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



using namespace ev3api;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
static UCHR  bt_cmd    = '0';         /* Bluetoothコマンド 1:リモートスタート */
FILE* gBtHandle = NULL;      /* Bluetoothファイルハンドル */
// static FILE* gBtHandle = NULL;      /* Bluetoothファイルハンドル */

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define CMD_RIGHIT        ('1')    /* リモートスタートコマンド */
#define RIGHIT_ID         (0)    /* シナリオ指定ID */
#define CMD_LEFT          ('2')    /* リモートスタートコマンド */
#define LEFT_ID           (50)    /* シナリオ指定ID */

#define SCENE_Q    (  45 )
#define SCENE_W    (  46 )
#define SCENE_E    (  47 )
#define SCENE_R    (  48 )
#define SCENE_T    (  49 )
#define SCENE_Y    (  95 )
#define SCENE_U    (  96 )
#define SCENE_I    (  97 )
#define SCENE_O    (  98 )
#define SCENE_P    (  99 )
#define SCENE_Z    ( 100 )
#define SCENE_X    (  93 )

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* オブジェクトへのポインタ定義 */
TouchSensor*    touchSensor;
SonarSensor*    sonarSensor;
ColorSensor*    colorSensor;
GyroSensor*     gyroSensor;
Motor*          leftMotor;
Motor*          rightMotor;
Motor*          tailMotor;
Clock*          clock;


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

static void user_system_create( void );
static void user_system_destroy( void );
static bool SetingFileload( char* f_pass, memfile_t* ev3_file_stc );//SDカード->オブジェクト
static bool SetingFileWrite( char* f_pass, FILE* bt_handle );//BT->SDカード


void main_task(intptr_t unused)
{
    ev3_led_set_color(LED_OFF);

    user_system_create();  // センサやモータの初期化処理

    ev3_led_set_color(LED_GREEN);

    // 周期ハンドラ開始
    ev3_sta_cyc(EV3_CYC_TRACER);

    // Bluetooth通信タスクの起動
    act_tsk(BT_TASK);

    //基本動作タスクの開始
    act_tsk(TRACER_TASK);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(EV3_CYC_TRACER);
    /* Bluetooth通信タスクの破棄 */
    ter_tsk(BT_TASK);
    /* 基本動作タスクの破棄 */
    ter_tsk(TRACER_TASK);
    
    user_system_destroy();  // 終了処理

    ext_tsk();
}

static void user_system_create( void )
{
    memfile_t PidSetStract;
    memset( &PidSetStract, 0,sizeof( PidSetStract ));

    /* 各オブジェクトを生成・初期化する */
    touchSensor = new TouchSensor(PORT_1);
    colorSensor = new ColorSensor(PORT_3);
    //sonarSensor = new SonarSensor(PORT_2);
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

    //Bluetooth
    gBtHandle = ev3_serial_open_file( EV3_SERIAL_BT );
    assert( gBtHandle != NULL );

    SetingFileload(( char* )PID_SET_FILE_PASS, &PidSetStract );
    ev3_memfile_free( &PidSetStract );

    fprintf( gBtHandle,"[system_create]\r\n");

    return;
}

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

void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(INTERRUPT_TASK);
}

void interrupt_task(intptr_t exinf) {
    volatile static int dummy = 0;
    //センシング
    gGyroAdmin->callValueUpdate();//stop
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

    //OS最適化防止ダミー計算
    dummy++;

    // fprintf( gBtHandle,"%d\r\n", (int)gRayReflectAdmin->getValue());

#ifdef INTERRUPT_CHK
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

    ext_tsk();
}

void tracer_task(intptr_t exinf) {
    bool sceneGo = true;
    while( ev3_button_is_pressed( BACK_BUTTON ) == false ) {
        sceneGo = gScenarioConductor->execScenario();//メインタスク
        if( sceneGo == false ) { break; }
        if( ev3_button_is_pressed(BACK_BUTTON)) { break; }
    }
    ev3_led_set_color(LED_RED);
    gScenarioConductor->quitCommand();
    // clock->sleep(500);
    wup_tsk(MAIN_TASK);  // バックボタン押下
}

//*****************************************************************************
// 関数名 : bt_task
// 引数 : unused
// 返り値 : なし
// 概要 : Bluetooth通信によるリモートスタート。 Tera Termなどのターミナルソフトから、
//       ASCIIコードで1を送信すると、リモートスタートする。
//*****************************************************************************
void bt_task(intptr_t unused)
{
    int32_t lTilOfset = 0;
    memfile_t PidSetStract;
    int16_t  cRefOfs  = OFFSET_REF;
    SCHR bt_cmd_ = 0;
    memset( &PidSetStract, 0,sizeof( PidSetStract ));

    while( true )
    {
#ifdef SOUND_ANSWER
        ev3_speaker_play_tone( NOTE_C4, 80 );
#endif

        bt_cmd_ = fgetc(gBtHandle); /* 受信 */
        bt_cmd = bt_cmd_;
        // serial_rea_dat(SIO_PORT_BT, (char*)&bt_cmd, 1);

        switch( bt_cmd ) {
            case CMD_RIGHIT://右コースセット
                gScenarioConductor->setScenario( RIGHIT_ID );
                break;
            case CMD_LEFT://左コース
                gScenarioConductor->setScenario( LEFT_ID );
                break;
            case 'S'://ファイル読み込み
                SetingFileWrite(( char* )PID_SET_FILE_PASS, gBtHandle );
                SetingFileload(( char* )PID_SET_FILE_PASS, &PidSetStract );
                ev3_memfile_free( &PidSetStract );
                break;
            case 'B'://Bluetooth通信の終了
#ifdef SOUND_ANSWER
                ev3_speaker_play_tone( NOTE_C4, 240 );
#endif
                goto EXIT;
                break;

            case 'X':
                gScenarioConductor->setScenario( SCENE_X );
                break;
            case 'z':
                gScenarioConductor->setScenario( SCENE_Z );
                break;
            // case 'h':
            //     ev3_stp_cyc(EV3_CYC_TRACER);
            //     gGyroAdmin->callValueUpdate();//stop
            //     ev3_sta_cyc(EV3_CYC_TRACER);
                
            //     break;

            case 'q':
                gScenarioConductor->setScenario( SCENE_Q );
                break;
            case 'w':
                gScenarioConductor->setScenario( SCENE_W );
                break;
            case 'e':
                gScenarioConductor->setScenario( SCENE_E );
                break;
            case 'r':
                gScenarioConductor->setScenario( SCENE_R );
                break;
            case 't':
                gScenarioConductor->setScenario( SCENE_T );
                break;
            case 'y':
                gScenarioConductor->setScenario( SCENE_Y );
                break;
            case 'u':
                gScenarioConductor->setScenario( SCENE_U );
                break;
            case 'i':
                gScenarioConductor->setScenario( SCENE_I );
                break;
            case 'o':
                gScenarioConductor->setScenario( SCENE_O );
                break;
            case 'p':
                gScenarioConductor->setScenario( SCENE_P );
                break;
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
            case 'N':
                cRefOfs++;
                fprintf( gBtHandle,"<%d>\r\n", (int)cRefOfs );
                gRunLineCalculator->setOffsetREf( cRefOfs );
                break;
            case 'M':
                cRefOfs--;
                fprintf( gBtHandle,"<%d>\r\n", (int)cRefOfs );
                gRunLineCalculator->setOffsetREf( cRefOfs );
                break;
            default:
                break;
        }
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

EXIT:
    fprintf( gBtHandle,"See you !\r\n");
    return;
}

static bool SetingFileload( char* f_pass, memfile_t* ev3_file_stc )
{
    /* ファイル構造体の生成 */
    EV3_SETTING  strcEv3File;
    ER ret;
    memset( &strcEv3File, 0, sizeof(EV3_SETTING));

    /* 異常終了：ぬるぽ */
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

    PID_SETTING* test;

    test = gRunLineCalculator->isGain();

    fprintf( gBtHandle,"nm[%f][%f]sc[%f][%f]\r\n",
        ( test + 0 )->fTerSpeed,( test + 0 )->fTerRefLv, 
        ( test + 1 )->fTerSpeed,( test + 1 )->fTerRefLv );
    return true;
}

static bool SetingFileWrite( char* f_pass, FILE* bt_handle )
{
    FILE* SDFileH = NULL;
    /* ファイル構造体の生成（一時受け用） */
    int8_t  cDummy[sizeof(EV3_SETTING)];
    memset( &cDummy[0], 0, 100);

    /* 異常終了：ぬるぽ */
    if( f_pass == NULL ) { return false; }
    if( bt_handle == NULL ) { return false; }

    /* ユーザーレスポンス */
    fprintf( gBtHandle,"----FILE IN----\r\n" ); /* エコーバック */
#ifdef SOUND_ANSWER
    ev3_speaker_play_tone( NOTE_C4, 500 );
#endif
    /* Bt受付 */
    fread( cDummy, sizeof(char), sizeof(EV3_SETTING), bt_handle );

    /* ユーザーレスポンス */
    fprintf( gBtHandle,"--FILE COMMIT--\r\n" ); /* エコーバック */
#ifdef SOUND_ANSWER
    ev3_speaker_play_tone( NOTE_C4, 500 );
#endif
    /* 一時受けからSDカードへ書き込み */
    SDFileH = fopen( f_pass, "wb" );//ファイルオープン
    if( SDFileH != NULL ) {
        fwrite( cDummy, sizeof(char), sizeof(cDummy), SDFileH );//書き込み
        fclose( SDFileH );//SDファイルクローズ
    }

    return true;
}
