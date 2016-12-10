/* ---------------------------------------------------------------------------------------------- */
// Balancer_ohs.h
// EV3_HAL2016\計算機能\バランサー
// EV3倒立振子制御を行う。大会提供API「balancer.c」を用いる。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// BL0000  2016/06/12  大塚　信晶  新規作成
// BL0001  2016/07/21  大塚　信晶  コンパイルチェック
// BL0002  2016/08/18  大塚　信晶  バランサーON/OFF対応＠init()メソッド
/* ---------------------------------------------------------------------------------------------- */

#ifndef CALCULATION_BALANCER_OHS_H_
#define CALCULATION_BALANCER_OHS_H_

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */
#include "balancer.h"                       //大会提供バランサーAPI
#include "ev3api.h"                         //大会提供API＠基本ヘッダー
#include "../device_ope/GyroAdmin_ohs.h"    //ジャイロセンサ管理者

/* ---------------------------------------------------------------------------------------------- */
// 定数定義
/* ---------------------------------------------------------------------------------------------- */
#define BL_K_GY_OFFS (      0.02F )
//#define BL_K_GY_OFFS (      0.0F )

/* ---------------------------------------------------------------------------------------------- */
// クラス名     ：Balancer_ohs
// 役割名       ：倒立振子制御
// 役割概要     ：EV3本体が倒立振子制御を行う為に、各センサ値から最適なモータ出力値を計算する。
// 作成日       ：2016/06/12  大塚　信晶＠新規作成
/* ---------------------------------------------------------------------------------------------- */
class Balancer_ohs {
public:
    /* パブリック ------------------------------------------------------------------------------- */
    Balancer_ohs( GyroAdmin_ohs* gyro_admin );// コンストラクタ
    ~Balancer_ohs();// デストラクタ

    BOOL calcPWM( int8_t spd, int8_t deg, void* running_admin );// 倒立振子モータ値計算
    void init();// バランサー初期化

    /* 計算結果出力 */
    int8_t isRightPWM( void );// 右
    int8_t isLeftPWM( void ); // 左
    /* テスト用メソッド(非公開) */
    void  setOffSet( FLOT set_offset );// ジャイロ値オフセット強制変更

private:
    /* プライベート ----------------------------------------------------------------------------- */
    GyroAdmin_ohs* mGyroAdmin;// ジャイロセンサ値取得用
    FLOT   mRdOffSet;   // balancer.c初期化後起動用右回転値オフセット
    FLOT   mLdOffSet;   // balancer.c初期化後起動用左回転値オフセット
    FLOT   mGyOffSet;   // 高速走行用ジャイロ値補完用オフセット
    int8_t mRightPwm;   // 右モータ出力値の回転出力値計算結果
    int8_t mLeftPwm;    // 左モータ出力値の回転出力値計算結果
    BOOL   mInit;       // 初期化完了フラグ
};

#endif/* CALCULATION_BALANCER_OHS_H_ */
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
