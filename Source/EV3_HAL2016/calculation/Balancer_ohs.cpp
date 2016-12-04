/* ---------------------------------------------------------------------------------------------- */
// Balancer_ohs.cpp
// EV3_HAL2016\計算機能\バランサー
// EV3倒立振子制御を行う。大会提供API「balancer.c」を用いる。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// 000000  2016/06/12  大塚　信晶  新規作成
// 000001  2016/07/21  大塚　信晶  コンパイルチェック
// 000002  2016/08/18  大塚　信晶  バランサーON/OFF対応＠init()メソッド
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */
#include "hal_ev3_std.h"                        // HAL_EV3大会用　標準ヘッダ
#include "../device_ope/RunningAdmin_ohs.h"     // 走行管理者
#include "Balancer_ohs.h"                       // バランサー

/* ---------------------------------------------------------------------------------------------- */
// クラス名     ：Balancer_ohs
// 役割名       ：倒立振子制御
// 役割概要     ：EV3本体が倒立振子制御を行う為に、各センサ値から最適なモータ出力値を計算する。
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]GyroAdmin_ohs* gyro_admin : ジャイロセンサ管理者
/* ---------------------------------------------------------------------------------------------- */
Balancer_ohs::Balancer_ohs( GyroAdmin_ohs* gyro_admin )
:mGyroAdmin( gyro_admin )
{
    mRightPwm = 0;      // 右モータ出力値の回転出力値計算結果
    mLeftPwm  = 0;      // 左モータ出力値の回転出力値計算結果
    mGyOffSet = 0;      // 高速走行用ジャイロ値補完用オフセット
    mRdOffSet = 0;      // balancer.c初期化後起動用右回転値オフセット
    mLdOffSet = 0;      // balancer.c初期化後起動用左回転値オフセット
    balance_init();     // 倒立振子制御初期化
    mInit     = false;  // 初期化済みフラグ＠初期化未完
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：~Balancer_ohs
// 機能名       ：デストラクタ
// 機能概要     ：オブジェクトの破棄
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* ---------------------------------------------------------------------------------------------- */
Balancer_ohs::~Balancer_ohs() {
}

/* パブリック ----------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：calcPWM
// 機能名       ：倒立振子モータ値計算
// 機能概要     ：倒立振子制御に必要なモータ回転数を算出する。＠balancer.cを使用
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]int8_t spd : 目標走行速度
// [I N]int8_t deg : 目標旋回速度
// [I N]void* running_admin : 走行管理者＠モータ回転数の取得のみの目的
/* 戻り値 [long] -------------------------------------------------------------------------------- */
// true  : 正常終了
// false : 異常終了
/* ---------------------------------------------------------------------------------------------- */
BOOL Balancer_ohs::calcPWM( int8_t spd, int8_t deg, void* running_admin ) {
    /* 変数宣言 --------------------------------------------------------------------------------- */
    FLOT fGyroValue = 0;    // ジャイロ値FLOT型変換用
    FLOT fNowRDeg = 0;      // 右モータ回転値FLOT型変換用
    FLOT fNowLDeg = 0;      // 左モータ回転値FLOT型変換用
    FLOT fBattery = 0;      // バッテリ値FLOT型変換用
    RunningAdmin_ohs* RunningAdmin = ( RunningAdmin_ohs* )running_admin;// オブジェクトPの取得

    /* 引数取得 --------------------------------------------------------------------------------- */
    // ジャイロ値の取得
    fGyroValue =   ( FLOT )mGyroAdmin->getValue();
    // fGyroValue =   ( FLOT )mGyroAdmin->getFilterValue();

    // モータ回転値の取得
    fNowRDeg = ( FLOT )RunningAdmin->isRightRotary();
    fNowLDeg = ( FLOT )RunningAdmin->isLeftRotary();

    //バッテリー残量の取得
    fBattery = ( FLOT )ev3_battery_voltage_mV();

    /* ------------------------------------------------------------------------------------------ */
    // イニシャライズのチェック＠balancer.cの初期化を行った後に必要な処理
    /* ------------------------------------------------------------------------------------------ */
    if( mInit == false ) {
        mRdOffSet = fNowRDeg;// 右モータ回転値のbalance_controlへの引数調整
        mLdOffSet = fNowLDeg;// 左モータ回転値のbalance_controlへの引数調整
        mInit = true;// 初期化フラグ＠初期化完了
    }
    /* 回転値オフセット効果 */
    fNowRDeg -= mRdOffSet;
    fNowLDeg -= mLdOffSet;

    //ジャイロオフセット値の調整
    //mGyOffSet = ( FLOT )spd * BL_K_GY_OFFS;

    /* 倒立振子制御APIを呼び出し、倒立走行するための左右モータ出力値を得る */
    balance_control(
        static_cast<float>(spd),
        static_cast<float>(deg),
        static_cast<float>( fGyroValue ),
        static_cast<float>( mGyOffSet ),
        static_cast<float>( fNowLDeg ),
        static_cast<float>( fNowRDeg ),
        static_cast<float>( fBattery ),
        &mLeftPwm,
        &mRightPwm);

    return true;// 正常終了＠引数チェック追加してね♡
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：isRightPWM
// 機能名       ：計算結果出力
// 機能概要     ：メソッド「calcPWM」計算結果の出力
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* 戻り値 [int8_t] ------------------------------------------------------------------------------ */
// -100 ～ 100 : 右モータ回転指示値計算結果
/* ---------------------------------------------------------------------------------------------- */
int8_t Balancer_ohs::isRightPWM() {
    return ( mRightPwm );
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：isLeftPWM
// 機能名       ：計算結果出力
// 機能概要     ：メソッド「calcPWM」計算結果の出力
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* 戻り値 [int8_t] ------------------------------------------------------------------------------ */
// -100 ～ 100 : 左モータ回転指示値計算結果
/* ---------------------------------------------------------------------------------------------- */
int8_t Balancer_ohs::isLeftPWM() {
    return ( mLeftPwm );
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：init
// 機能名       ：バランサー初期化
// 機能概要     ：バランサーOFFからON時に必ず必要。balancer.c内の各パラメータ値を初期化する
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* ---------------------------------------------------------------------------------------------- */
void Balancer_ohs::init() { balance_init(); mInit = false; }

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：setOffSet
// 機能名       ：【テスト】バランス値の外部制御
// 機能概要     ：バランス走行の走行速度向上実験用。本体加速度と角加速度の関係性の調査
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]FLOT set_offset : ジャイロ値オフセット値
/* ---------------------------------------------------------------------------------------------- */
void  Balancer_ohs::setOffSet( FLOT set_offset )
{
   mGyOffSet =  set_offset;
}

/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
