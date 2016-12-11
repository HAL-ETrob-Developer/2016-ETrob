/* ---------------------------------------------------------------------------------------------- */
// RunLineCalculator_ohs.h
// EV3_HAL2016\計算機能\走行線計算器
// ライントレース時の走行線計算を行う。PID制御を用いる。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// RL0000  2016/07/17  大塚　信晶  新規作成
// RL0001  2016/07/23  大塚　信晶  ライントレース新機能実装＠光量直接使用＋シンプルライントレース
// RL0002  2016/07/25  大塚　信晶  ゲイン値外部編集機能の実装
// RL0003  2016/09/16  大塚　信晶  バグフィックス
/* ---------------------------------------------------------------------------------------------- */

#ifndef CALCLATION_RUNLINECALCULATOR_OHS_H_
#define CALCLATION_RUNLINECALCULATOR_OHS_H_

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include "ev3api.h" //大会提供API＠基本ヘッダー

/* ---------------------------------------------------------------------------------------------- */
// 定数定義
/* ---------------------------------------------------------------------------------------------- */

#define OFFSET_REF   (          0 )// 計算時反射光量オフセット値( 過去値 25 )

#define SPEED_ID     (          0 )// 設定ファイル取り込みID＠通常＠速度ゲイン
#define DEGRE_ID     (          1 )// 設定ファイル取り込みID＠通常＠角度ゲイン
#define SPEED_ID_S   (          2 )// 設定ファイル取り込みID＠特殊＠速度ゲイン
#define DEGRE_ID_S   (          3 )// 設定ファイル取り込みID＠特殊＠角度ゲイン
#define K_ID_NUM     (          4 )// ゲイン値保持メンバ生成個数

#define NORMAL_ID    (          0 )// PID設定格納ファイルID＠通常
#define SECOND_ID    (          1 )// PID設定格納ファイルID＠特殊
#define PID_SET_N    (          2 )// PID設定格納ファイル格納用メンバ生成個数

#define TRGE_N_ID    (          0 )// 走行速度・角度目標値ID＠通常
#define TRGE_S_ID    (          1 )// 走行速度・角度目標値ID＠特殊
#define RLT_SET_N    (          2 )// 走行目標値格納用メンバ生成個数＠RunLinecalculatorTerget=RLT

#define TERGET_SPD   (      80.0F )// 目標走行速度＠通常初期値
#define TERGET_SPD_S (      30.0F )// 目標走行速度＠特殊初期値
#define T_MIN_SPD    (      20.0F )// 最低走行速度
#define TERGET_DEG   (       0.0F )// 目標走行角度＠共用

#define TERGET_LV    (      70.0F )// 目標光学センサ反射値＠通常
#define TERGET_LV_S  (      40.0F )// 目標光学センサ反射値＠特殊

/* ゲイン 初期値 -------------------------------------------------------------------------------- */
// PID N
#define K_P_SPD     (     0.008F )
#define K_I_SPD     (     0.001F )
#define K_D_SPD     (      0.04F )
#define K_P_DEG     (       0.2F )
#define K_I_DEG     (       0.1F )
#define K_D_DEG     (      15.0F )
// PID S
#define K_P_SPD_S   (       0.0F )
#define K_I_SPD_S   (       0.0F )
#define K_D_SPD_S   (       0.0F )
#define K_P_DEG_S   (       1.0F )
#define K_I_DEG_S   (       0.5F )
#define K_D_DEG_S   (       4.0F )

/* ゲイン 実験履歴 ------------------------------------------------------------------------------ */
// 3ms割り込み言い感じ
// #define K_P_SPD     (       0.008F )
// #define K_I_SPD     (       0.001F )
// #define K_D_SPD     (       0.04F )
// #define K_P_DEG     (       0.2F )
// #define K_I_DEG     (       0.1F )
// #define K_D_DEG     (      12.0F )

// 良い感じ
// #define K_P_SPD     (       0.008F )
// #define K_I_SPD     (       0.0F )
// #define K_D_SPD     (       0.01F )
// #define K_P_DEG     (       0.30F )
// #define K_I_DEG     (       0.035F )
// #define K_D_DEG     (       6.0F )

// なかなか
// #define K_P_SPD     (       0.006F )
// #define K_I_SPD     (       0.0F )
// #define K_D_SPD     (       0.04F )
// #define K_P_DEG     (       0.08F )
// #define K_I_DEG     (       0.25F )
// #define K_D_DEG     (       5.0F )

// 原点
// #define K_P_SPD     (       0.003F )
// #define K_I_SPD     (       0.0F )
// #define K_D_SPD     (       0.06F )
// #define K_P_DEG     (       0.08F )
// #define K_I_DEG     (       0.25F )
// #define K_D_DEG     (       5.0F )

/* ---------------------------------------------------------------------------------------------- */
// クラス名     ：RunLineCalculator_ohs
// 役割名       ：走行線計算器
// 役割概要     ：ライントレースを行う為に光学センサ値より最適な走行速度・角度を算出する。
//                PID制御を用い、各ゲイン値は設定ファイルにより管理される。
// 作成日       ：2016/07/17  大塚　信晶＠新規作成
/* ---------------------------------------------------------------------------------------------- */
class RunLineCalculator_ohs {
    public:/* ------------------------------------------------------------------------ パブリック */
        /* オブジェクトの生成 */
        RunLineCalculator_ohs();// コンストラクタ
        ~RunLineCalculator_ohs();// デストラクタ

        BOOL calcRunLine( BOOL speed_trac, SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg );// 走行線計算
        void setParametersInit();// 現在のPID値をすべてクリアする
        void setGain( PID_SETTING* p_set_file );// 設定ファイルの読み込み

        int8_t getSpeed();// 算出走行速度の出力
        int8_t getDeg();// 算出走行角度の出力

        /* テスト用メソッド(非公開) */
        BOOL setOffsetREf( int16_t degOffset );// 取得光量オフセット
        PID_SETTING* isGain( void );// 現在使用中の各ゲイン値の出力
        FLOT isP( void );// 現在基本比例値の出力＠Proportional
        FLOT isI( void );// 現在基本積分値の出力＠Integral
        FLOT isD( void );// 現在基本微分値の出力＠Differential

    private:/* --------------------------------------------------------------------- プライベート */

        /* メソッド */
        void calcRunLineUseRefLv( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg );// 走行線計算＠通常
        void calcRunLineSecondLine( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg );// 走行線計算＠特殊（特にメソッド分けてる意味は無いです。テストとかで活用してください。現状高速ライントレース用）

        /* メンバ */
        FLOT mPValue[K_ID_NUM];// 比例値保持
        FLOT mIValue[K_ID_NUM];// 積分値保持
        FLOT mDValue[K_ID_NUM];// 微分値保持

        PID_SETTING mPidGainF[PID_SET_N];// ゲイン設定ファイル格納用

        FLOT mTergetSpeed[RLT_SET_N];// 目標走行速度格納用
        FLOT mTergetRefLV[RLT_SET_N];// 目標光学センサ反射値格納用
        FLOT mKP[K_ID_NUM];// Pゲイン格納用
        FLOT mKI[K_ID_NUM];// Iゲイン格納用
        FLOT mKD[K_ID_NUM];// Dゲイン格納用

        int8_t  mSpeed;// 走行速度計算結果
        int8_t  mDeg;// 走行角度計算結果
        int16_t mOffsetRef;// 取得光学値に対するオフセット値

        BOOL mInitF;// パラメータ初期化フラグ

};// class RunLineCalculator_ohs

#endif/* CALCULATION_RUNLINECALCULATOR_OHS_H_ */
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
