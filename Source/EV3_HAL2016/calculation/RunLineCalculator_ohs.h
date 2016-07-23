/* by ohs50465 T.UENO */
#ifndef CALCLATION_RUNLINECALCULATOR_OHS_H_
#define CALCLATION_RUNLINECALCULATOR_OHS_H_

#include "ev3api.h"

/* define file */

#define DEF_ADD     (      0.10F )

#define TERGET_SPD  (      60.0F )
#define MAX_CW_DEG  (       0.0F )
#define MAX_CCW_DEG (       0.0F )

#define DEF_TERGET  (       0.0F )

#define TERGET_LV   (      50.0F )

/* ゲイン変更 ----------------------------------------------------------------------------------- */
#define USE_REFLV 
#ifdef USE_REFLV//calcRunLineUseRefLv使用

#define K_P_SPD     (       0.0F )
#define K_I_SPD     (       0.0F )
#define K_D_SPD     (       0.0F )
#define K_P_DEG     (       0.3F )
#define K_I_DEG     (       0.0F )
#define K_D_DEG     (       0.2F )

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
    FLOT isP(void);
    FLOT isI(void);
    FLOT isD(void);

private:
	/* メンバ */
    int8_t mSpeed;
    int8_t mDeg;
    FLOT mPValue;
    FLOT mIValue;
    FLOT mDValue;

};

#endif  // RUNLINECALCULATOR_OHS_H_
