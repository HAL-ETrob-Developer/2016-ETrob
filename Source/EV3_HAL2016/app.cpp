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
static int32_t   bt_cmd = 0;      /* Bluetoothコマンド 1:リモートスタート */
static FILE*     gBtHandle = NULL;      /* Bluetoothファイルハンドル */

/* 設定ファイル */
static memfile_t     gPidSetStract;      /* 設定ファイルハンドル */

static int8_t gSpd = 0;//test Mod
static FLOT   gGyOffSet = 0;//test Mod

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define CMD_START         '1'    /* リモートスタートコマンド */

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


static void user_system_create( void );
static void user_system_destroy( void );
static void PidFileLood( memfile_t* pid_file_stc );
static void PidFileWrite( memfile_t* pid_file_stc, char cmd );


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
    ER ret;
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
  
    gEvStateAdmin = new EvStateAdmin_ohs( gRayReflectAdmin, gGyroAdmin, gRunningAdmin, gTailAdmin );
    gLineTracer   = new LineTracer_ohs( gRunningAdmin, gRayReflectAdmin, gRunLineCalculator );
    gPatternSequencer  = new PatternSequencer_ohs( gRunningAdmin, gTailAdmin );
    gScenarioConductor = new ScenarioConductor_ohs( gEvStateAdmin, gLineTracer, gPatternSequencer );

    //Bluetooth
    gBtHandle = ev3_serial_open_file( EV3_SERIAL_BT );
    assert( gBtHandle != NULL );

    memset( &gPidSetStract, 0, sizeof(gPidSetStract));
    ret  =  ev3_memfile_load( PID_SET_FILE_PASS, &gPidSetStract );
    assert( ret != E_OK );

   PidFileLood( &gPidSetStract );

    return;
}

static void user_system_destroy( void )
{
    FILE* pidSetFileH = NULL;

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



    if( touchSensor        ) { delete touchSensor;        touchSensor        = NULL; }
    if( colorSensor        ) { delete colorSensor;        colorSensor        = NULL; }
    if( sonarSensor        ) { delete sonarSensor;        sonarSensor        = NULL; }
    if( gyroSensor         ) { delete gyroSensor;         gyroSensor         = NULL; }
    if( leftMotor          ) { delete leftMotor;          leftMotor          = NULL; }
    if( rightMotor         ) { delete rightMotor;         rightMotor         = NULL; }
    if( tailMotor          ) { delete tailMotor;          tailMotor          = NULL; }
    if( clock              ) { delete clock;              clock              = NULL; }

    if( gBtHandle != NULL )  { fclose(gBtHandle); }

    if( gPidSetStract.buffer != NULL )  {
        pidSetFileH =  fopen( PID_SET_FILE_PASS, "wb" );
        if( pidSetFileH != NULL ) {
            fwrite( gPidSetStract.buffer,
                  sizeof(char),
                  sizeof(PID_SETTING) ,
                  pidSetFileH );
            fclose( pidSetFileH );
        }
        ev3_memfile_free( &gPidSetStract );
    }

    return;
}

void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(INTERRUPT_TASK);
}

void interrupt_task(intptr_t exinf) {
    //センシング
    gGyroAdmin->callValueUpdate();
    gRunningAdmin->callValueUpDate();
    gRayReflectAdmin->callValueUpDate();
    gTailAdmin->callValueUpDate();

    //制御
    gLineTracer->callLineTraceAct();
    //gLineTracer->callSimplLineTraceAct();

    //アクチュエイト
    gRunningAdmin->callRunning();
    gTailAdmin->callActDegree();

#ifdef INTERRUPT_CHK
    static int tes = 0;
    tes++;
    if( tes > 124 ) {
        ev3_speaker_play_tone( NOTE_E6, 10 );
        tes = 0;
    }
#endif
#ifdef LT_DEBUG
    fprintf( gBtHandle, "[P = %3.3f ][I = %3.3f ] [D = %3.3f]\r\n", 
            gRunLineCalculator->isP(), gRunLineCalculator->isI(), gRunLineCalculator->isD());
#endif
#ifdef REFST_DEBUG
    if( gRayReflectAdmin->getState() == SCLR_GRAY ) {
        fprintf( gBtHandle, "[SCLR_GRAY]\r\n");
    }
#endif
    ext_tsk();
}

void tracer_task(intptr_t exinf) {
    while( ev3_button_is_pressed( BACK_BUTTON ) == false ) {
        switch( bt_cmd ) {
            case 0:
                gTailAdmin->postTailDegree(90);
                break;
            case 3:
            case 2:
                // gBalancer->setOffSet( gGyOffSet );
            case 1:
                gLineTracer->postLineTraceStop();//ライントレースストップ
                gRunningAdmin->postRunning(gSpd,0,true);
                gTailAdmin->postTailDegree(0);
                break;
            case 4:
                gRunningAdmin->postRunning(0,50,true);
                gTailAdmin->postTailDegree(0);
                break;
            case 5:
                gRunningAdmin->postRunning(0,-50,true);
                gTailAdmin->postTailDegree(0);
                break;
            case 7:
                gRunningAdmin->postRunning(0,0,true);
                gTailAdmin->postTailDegree(0);
                break;
            case 'e':
                goto EXIT;
                break;
            case 't':
                gLineTracer->postLineTraceConduct();
                break;
            default:
                break;
        }
    }
EXIT:
    ev3_led_set_color(LED_RED);
    gLineTracer->postLineTraceStop();//ライントレースストップ
    gRunningAdmin->postRunning(0,0,false);//走行停止
    gTailAdmin->postTailDegree(0);//尻尾復帰
    clock->sleep(500);
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
    while(1)
    {
        ev3_speaker_play_tone( NOTE_C4, 80 );
        uint8_t c = fgetc(gBtHandle); /* 受信 */
        switch(c)
        {
        case '0':
            break;
        case '1':
            bt_cmd = 1;
            break;
        case '2':
            gSpd -= 10;
            // gGyOffSet--;
            bt_cmd = 2;
            break;
        case '3':
            gSpd += 10;
            // gGyOffSet++;
            bt_cmd = 3;
            break;
        case '4':
            bt_cmd = 4;
            break;
        case '5':
            bt_cmd = 5;
            break;
        case '7':
            bt_cmd = 7;
            break;
        case 'e':
            bt_cmd = 'e';
            break;
        case 't':
            bt_cmd = 't';
            break;
        case 's':
            /* 設定ファイルの書き込み */
            // PidFileWrite( &gPidSetStract,c );

            fprintf( gBtHandle,"[%c]---FILE IN----\r\n",c ); /* エコーバック */
            ev3_speaker_play_tone( NOTE_C4, 500 );

            /* Bt受付 */
            fread( gPidSetStract.buffer,
                    sizeof(char),
                    sizeof(PID_SETTING),
                    gBtHandle );

            /* ユーザーレスポンス */
            ev3_speaker_play_tone( NOTE_C4, 500 );
            
            break;
        case '9':
            bt_cmd = 9;
            gGyroAdmin->initDegree();
            break;
        default:
            break;
        }
        if( gPidSetStract.buffer != NULL ) {
            fprintf( gBtHandle, "buffer[%s]PID_SETTING[%d]buffersz[%d]\r\n", 
            (char*)(gPidSetStract.buffer), sizeof(PID_SETTING), gPidSetStract.buffersz );
        }

        fprintf( gBtHandle, "[speed = %3d ][deg = %3d ] [gSpd = %3d][cmd = %c]\r\n", 
                gRunningAdmin->getSpeed(), gRunningAdmin->getAngle(), gSpd,c );
        //fputc(c, gBtHandle); /* エコーバック */
    }
}

static void PidFileLood( memfile_t* pid_file_stc )
{
    /* ファイル構造体の生成 */
    PID_SETTING  strcPidFile;
    memset( &strcPidFile, 0, sizeof(PID_SETTING));

    /* 異常終了 */
    if( pid_file_stc->buffersz < sizeof(PID_SETTING) ) { return; }

    /* メモリ領域から構造体へ変換 */
    memcpy( &strcPidFile, pid_file_stc->buffer,sizeof(PID_SETTING));

    /* 設定ファイルのロード＠パラメタ変更 */
    gRunLineCalculator->setGain( &strcPidFile );

    fprintf( gBtHandle,"[%s]s[%f][%f][%f]d[%f][%f][%f]\r\n",&strcPidFile,
            strcPidFile.fSpdP,strcPidFile.fSpdI,strcPidFile.fSpdD, 
            strcPidFile.fDegP,strcPidFile.fDegI,strcPidFile.fDegD );
    return;
}

static void PidFileWrite( memfile_t* pid_file_stc, char cmd )
{
    /* ファイル構造体の生成（一時受け用） */
    int8_t  cDummy[100];
    memset( &cDummy[0], 0, 100);

    /* ユーザーレスポンス */
    fprintf( gBtHandle,"[%c]---FILE IN----\r\n",cmd ); /* エコーバック */
    ev3_speaker_play_tone( NOTE_C4, 500 );

    /* Bt受付 */
    fread( cDummy,
            sizeof(char),
            sizeof(PID_SETTING),
            gBtHandle );

    /* ユーザーレスポンス */
    ev3_speaker_play_tone( NOTE_C4, 500 );

    /* 一時受けからメモリ領域へ */
    memcpy( pid_file_stc->buffer, cDummy, sizeof(PID_SETTING));

    /* 設定ファイルのロード */
    PidFileLood( pid_file_stc );

    return;
}
