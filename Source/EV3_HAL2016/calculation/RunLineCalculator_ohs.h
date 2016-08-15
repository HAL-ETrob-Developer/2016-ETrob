/* by ohs50465 T.UENO */
#ifndef CALCLATION_RUNLINECALCULATOR_OHS_H_
#define CALCLATION_RUNLINECALCULATOR_OHS_H_

#include "ev3api.h"

/* define file */

#define SPEED_ID     (      0 )
#define DEGRE_ID     (      1 )

#define DEF_ADD     (      0.10F )

#define TERGET_SPD  (      85.0F )
#define T_MIN_SPD   (      20.0F )

#define MAX_CW_DEG  (       0.0F )
#define MAX_CCW_DEG (       0.0F )

#define DEF_TERGET  (       0.0F )

#define TERGET_DEG  (       0.0F )
#define TERGET_LV   (      70.0F )

/* ゲイン変更 ----------------------------------------------------------------------------------- */
#define USE_REFLV 
#ifdef USE_REFLV//calcRunLineUseRefLv使用

#define K_P_SPD     (       0.008F )
#define K_I_SPD     (       0.001F )
#define K_D_SPD     (       0.04F )
#define K_P_DEG     (       0.2F )
#define K_I_DEG     (       0.1F )
#define K_D_DEG     (      15.0F )

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

#else//calcRunLine使用

#define K_P_SPD     (       0.0F )
#define K_I_SPD     (     0.007F )
#define K_D_SPD     (       0.0F )
#define K_P_DEG     (       0.5F )
#define K_I_DEG     (       0.0F )
#define K_D_DEG     (       3.0F )

#endif


class RunLineCalculator_ohs {
public:
    //生成
    RunLineCalculator_ohs();
    //デストラクタ
    ~RunLineCalculator_ohs();

    void calcRunLine( SENC_CLR color, int8_t* p_speed, int8_t* p_deg );
    void calcRunLineUseRefLv( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg );

    //テスト用メソッド(非公開)
    FLOT isP(void);
    FLOT isI(void);
    FLOT isD(void);
    void setGain( PID_SETTING* p_set_file );
    PID_SETTING* isGain( void );

private:
	/* メンバ */
    int8_t mSpeed;
    int8_t mDeg;
    FLOT mPValue[2];
    FLOT mIValue[2];
    FLOT mDValue[2];
    //ゲイン
    PID_SETTING mPidGainF;
    FLOT mKP[2];
    FLOT mKI[2];
    FLOT mKD[2];
};

#endif  // RUNLINECALCULATOR_OHS_H_
