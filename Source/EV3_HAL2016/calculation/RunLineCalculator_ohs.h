/* by ohs50465 T.UENO */
#ifndef CALCLATION_RUNLINECALCULATOR_OHS_H_
#define CALCLATION_RUNLINECALCULATOR_OHS_H_

#include "ev3api.h"

/* define file */

#define DEF_ADD     (      0.10F )

#define TERGET_SPD  (      80.0F )
#define MAX_CW_DEG  (       0.0F )
#define MAX_CCW_DEG (       0.0F )

#define DEF_TERGET  (       0.0F )

#define TERGET_LV   (      70.0F )

/* ゲイン変更 ----------------------------------------------------------------------------------- */
#define USE_REFLV 
#ifdef USE_REFLV//calcRunLineUseRefLv使用

#define K_P_SPD     (       0.005F )
#define K_I_SPD     (       0.0F )
#define K_D_SPD     (       1.0F )
#define K_P_DEG     (       0.35F )
#define K_I_DEG     (       0.04F )
#define K_D_DEG     (       7.0F )

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

private:
	/* メンバ */
    int8_t mSpeed;
    int8_t mDeg;
    FLOT mPValue;
    FLOT mIValue;
    FLOT mDValue;
    //ゲイン
    FLOT mKspdP;
    FLOT mKspdI;
    FLOT mKspdD;
    FLOT mKdegP;
    FLOT mKdegI;
    FLOT mKdegD;
};

#endif  // RUNLINECALCULATOR_OHS_H_
