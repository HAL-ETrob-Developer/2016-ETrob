/* by ohs50465 T.UENO */
#ifndef CALCLATION_RUNLINECALCULATOR_OHS_H_
#define CALCLATION_RUNLINECALCULATOR_OHS_H_

#include "ev3api.h"

/* define file */

#define SPEED_ID     (      0 )
#define DEGRE_ID     (      1 )
#define SPEED_ID_S   (      0 )/*2*/
#define DEGRE_ID_S   (      1 )/*3*/

#define NORMAL_ID    (      0 )
#define SCRCH__ID    (      1 )

#define DEF_ADD      (      0.10F )

#define TERGET_SPD   (      80.0F )
#define TERGET_SPD_S (      30.0F )
#define T_MIN_SPD    (       0.0F )

#define MAX_CW_DEG   (       0.0F )
#define MAX_CCW_DEG  (       0.0F )

#define DEF_TERGET   (       0.0F )

#define TERGET_DEG   (       0.0F )
#define TERGET_LV    (      70.0F )
#define TERGET_LV_S  (      40.0F )

/* ゲイン変更 ----------------------------------------------------------------------------------- */
#define K_P_SPD     (       0.008F )
#define K_I_SPD     (       0.001F )
#define K_D_SPD     (       0.04F )
#define K_P_DEG     (       0.2F )
#define K_I_DEG     (       0.1F )
#define K_D_DEG     (      15.0F )

#define K_P_SPD_S   (       0.0F )
#define K_I_SPD_S   (       0.0F )
#define K_D_SPD_S   (       0.0F )
#define K_P_DEG_S   (       1.0F )
#define K_I_DEG_S   (       0.5F )
#define K_D_DEG_S   (       4.0F )

//3ms割り込み言い感じ
// #define K_P_SPD     (       0.008F )
// #define K_I_SPD     (       0.001F )
// #define K_D_SPD     (       0.04F )
// #define K_P_DEG     (       0.2F )
// #define K_I_DEG     (       0.1F )
// #define K_D_DEG     (      12.0F )

//良い感じ
// #define K_P_SPD     (       0.008F )
// #define K_I_SPD     (       0.0F )
// #define K_D_SPD     (       0.01F )
// #define K_P_DEG     (       0.30F )
// #define K_I_DEG     (       0.035F )
// #define K_D_DEG     (       6.0F )

//なかなか
// #define K_P_SPD     (       0.006F )
// #define K_I_SPD     (       0.0F )
// #define K_D_SPD     (       0.04F )
// #define K_P_DEG     (       0.08F )
// #define K_I_DEG     (       0.25F )
// #define K_D_DEG     (       5.0F )

//原点
// #define K_P_SPD     (       0.003F )
// #define K_I_SPD     (       0.0F )
// #define K_D_SPD     (       0.06F )
// #define K_P_DEG     (       0.08F )
// #define K_I_DEG     (       0.25F )
// #define K_D_DEG     (       5.0F )



class RunLineCalculator_ohs {
public:
    //生成
    RunLineCalculator_ohs();
    //デストラクタ
    ~RunLineCalculator_ohs();

    void calcRunLine( BOOL line_check, SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg );
    //テスト用メソッド(非公開)
    FLOT isP(void);
    FLOT isI(void);
    FLOT isD(void);
    void setGain( PID_SETTING* p_set_file );
    PID_SETTING* isGain( void );

private:

    /* メソッド */
    void calcRunLineUseRefLv( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg );
    void calcRunLineCheckLine( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg );
	/* メンバ */
    int8_t mSpeed;
    int8_t mDeg;
    FLOT mPValue[4];
    FLOT mIValue[4];
    FLOT mDValue[4];
    //ゲイン
    PID_SETTING mPidGainF[2];

    FLOT mTergetSoeed[2];
    FLOT mTergetRefLV[2];
    FLOT mKP[4];
    FLOT mKI[4];
    FLOT mKD[4];
};

#endif  // RUNLINECALCULATOR_OHS_H_
