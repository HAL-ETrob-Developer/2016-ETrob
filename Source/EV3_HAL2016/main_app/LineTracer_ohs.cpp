/* ---------------------------------------------------------------------------------------------- */
// LineTracer_ohs.cpp
// EV3_HAL2016\基本機能\ライントレーサー
// コース上のラインを辿り走行する
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// LT0001  2016/07/15  大塚　信晶  新規作成
// LT0000  2016/07/17  大塚　信晶  実験・構想
// LT0002  2016/07/19  大塚　信晶  結合テスト
// LT0003  2016/07/23  大塚　信晶  PID制御の大幅変更
// LT0004  2016/08/20  大塚　信晶  シナリオ構成の変更に伴う影響範囲の調整
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include "ev3api.h"
#include "hal_ev3_std.h"
#include "LineTracer_ohs.h"

/* ---------------------------------------------------------------------------------------------- */
// クラス名     : LineTracer_ohs
// 役割名       : ライントレーサ
// 役割概要     : 大会コースライン上をトレース走行する為、デバイスの指示とライン計算の指示を行う
// 作成日       : 2016/07/15  大塚　信晶  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I/O]RunningAdmin_ohs* running_admin            : 光学センサ値取得用
// [I N]RayReflectAdmin_ohs* ray_reflect_admin     : 角加速度取得用
// [I/O]RunLineCalculator_ohs* run_line_calculator : 走行量取得用
/* ---------------------------------------------------------------------------------------------- */
LineTracer_ohs::LineTracer_ohs( RunningAdmin_ohs* running_admin, RayReflectAdmin_ohs* ray_reflect_admin, RunLineCalculator_ohs* run_line_calculator )
:mRunningAdmin(running_admin),/* 走行指示用＠コンストラクタ優先処理 */
 mRayReflectAdmin( ray_reflect_admin ),/* ライン監視用＠コンストラクタ優先処理 */
 mRunLineCalculator( run_line_calculator )/* 走行線計算＠コンストラクタ優先処理 */
{
    mLineTraceGo = false; // 初期化＠ライントレース停止
    mRapidMode   = false; // 初期化＠低速高精度トレース

    mGetColor = SCLR_GRAY;// 初期化＠グレー
    mSpeed = 0;
    mDeg   = 0;
    mGain  = 0;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : ~LineTracer_ohs
// 機能名       : デストラクタ
// 機能概要     : オブジェクトの破棄
// 作成日       : 2016/07/15  大塚　信晶  新規作成
/* ---------------------------------------------------------------------------------------------- */
LineTracer_ohs::~LineTracer_ohs() {}

/* パブリック ----------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : postLineTraceConduct
// 機能名       : ライントレース指示
// 機能概要     : ライントレースの実行を指示する。トレースの精度を選択する。
// 作成日       : 2016/07/15  大塚　信晶  新規作成
//              : 2016/08/20  大塚　信晶  シナリオ構成の変更に伴う影響範囲の調整
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]BOOL rapid_mode : トレースモード＠true_高速低精度 false_低速高精度
/* ---------------------------------------------------------------------------------------------- */
void LineTracer_ohs::postLineTraceConduct( BOOL rapid_mode ) {
    mLineTraceGo = true;
    mRapidMode   = rapid_mode;
    return;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : postLineTraceStop
// 機能名       : ライントレース停止
// 機能概要     : ライントレースの停止を指示する
// 作成日       : 2016/07/15  大塚　信晶  新規作成
/* ---------------------------------------------------------------------------------------------- */
void LineTracer_ohs::postLineTraceStop() {
    mLineTraceGo = false;
    // mRunLineCalculator->setParametersInit();
    return;
}


/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : callLineTraceAct
// 機能名       : ライントレース指示
// 機能概要     : ライントレースの実行を指示する。トレースの精度を選択する。
// 作成日       : 2016/07/15  大塚　信晶  新規作成
//              : 2016/08/20  大塚　信晶  シナリオ構成の変更に伴う影響範囲の調整
/* ---------------------------------------------------------------------------------------------- */
void LineTracer_ohs::callLineTraceAct() {
    static ULNG ulClrCounter = 0;// 白検知カウンター
    BOOL BrakeF_ = mRapidMode;   // トレースモード＝疑似ブレーキ

    /* 実行指揮の確認 */ 
    if( mLineTraceGo == false ) { return; }//ライントレース指揮無し

    /* 光学反射値の取得 */
    mGetColor = mRayReflectAdmin->getState();

    /* ラインが白か否かの判別 */
    if( mGetColor == SCLR_WHITE ) { ulClrCounter++; }

    /* ライン脱線判断 --------------------------------------------------------------------------- */
    if( ulClrCounter < SEARCH_SW ) {
        /* 白検知カウンタ安全域 */
        execLineEdgeTrace();// ライントレース
        ulClrCounter = 0;// 白検知カウンターリセット
    } else {
        /* 一定以上白を連続して検出 */
        // execLineSearch();// ライン探索開始
        execLineEdgeTrace();// ライン探索使わないです＠コンパイラの最適化でif自体無くなるといいな
    }

    /* 走行指示＠(走行速度,走行角度,バランス制御の有無,疑似ブレーキ) */
    mRunningAdmin->postRunning( mSpeed, mDeg, true, BrakeF_ );

    return;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : callSimplLineTraceAct
// 機能名       : シンプルライントレース＠デバック
// 機能概要     : ２値制御ライントレースの実行
// 作成日       : 2016/07/15  大塚　信晶  新規作成
//              : 2016/07/17  大塚　信晶  実験・構想
/* ---------------------------------------------------------------------------------------------- */
void LineTracer_ohs::callSimplLineTraceAct() {
    //実行指揮の確認 
    if( mLineTraceGo == false ) { return; }//ライントレース指揮無し
    /* 光学反射値の取得 */
    mGetColor = mRayReflectAdmin->getState();
  
    /* ラインが白か否かの判別 */
    if( mGetColor == SCLR_WHITE ) {
        mDeg = -LT_DEGRE_SLT;
    } else {
        mDeg = LT_DEGRE_SLT;
    }
    //走行速度の決定
    mSpeed = LT_SPEED_SLT;

    //走行指示＠(走行速度,走行角度,バランス制御の有無,疑似ブレーキ)
    mRunningAdmin->postRunning( mSpeed, mDeg, true,false );

    return;
}

/* プライベート --------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : execLineEdgeTrace
// 機能名       : ラインエッジトレース
// 機能概要     : PIDフィードバック制御を用いたライントレース
// 作成日       : 2016/07/15  大塚　信晶  新規作成
//              : 2016/07/23  大塚　信晶  PID制御の大幅変更
/* ---------------------------------------------------------------------------------------------- */
void LineTracer_ohs::execLineEdgeTrace() {
    /* 光学反射値の取得 */
    int16_t sRefVal = mRayReflectAdmin->getValue();

    /* ライン探索ゲインのリセット */
    mGain = 0;
    /* 左右モータの実指示値を取得＠calcRunLine内で結局使ってないです(保留) */
    mSpeed = mRunningAdmin->getSpeed();
    mDeg   = mRunningAdmin->getVector();

    /* PID計算 */
    mRunLineCalculator->calcRunLine( mRapidMode ,sRefVal, &mSpeed, &mDeg );

    /* 走行速度制限＠制限解除中 */
    // if( mSpeed > LT_MAX_SPEED ){
    //     mSpeed = LT_MAX_SPEED;
    // } else if( mSpeed < LT_MIN_SPEED ) {
    //     mSpeed = LT_MIN_SPEED;
    // }

    /* 旋回角度制限＠大会で急カーブできなかったのコイツのせい？ */
    if( mDeg > LT_MAX_DEGRE ){
        mDeg = LT_MAX_DEGRE;
    } else if( mDeg < LT_MIN_DEGRE ) {
        mDeg = LT_MIN_DEGRE;
    }

    return;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   : execLineSearch
// 機能名       : ライン探索＠使用不可
// 機能概要     : 脱線時にラインに復帰する。実用性なしの為、休止
// 作成日       : 2016/07/15  大塚　信晶  新規作成
//              : 2016/07/17  大塚　信晶  実験・構想
/* ---------------------------------------------------------------------------------------------- */
void LineTracer_ohs::execLineSearch()
{
    /* 固定速度で走行 */
    mSpeed = ( int8_t )( 30 );
    /* ゲイン比に基づき走行角度をCCWへ */
    mDeg = ( int8_t )( -50.0F * mGain );
    /* ライン探索ゲインの上昇 */
    mGain += RISE;
}

/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
