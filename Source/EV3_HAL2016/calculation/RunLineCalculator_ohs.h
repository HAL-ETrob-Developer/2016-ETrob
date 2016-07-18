/* by ohs50465 T.UENO */
#ifndef CALCLATION_RUNLINECALCULATOR_OHS_H_
#define CALCLATION_RUNLINECALCULATOR_OHS_H_

#include "ev3api.h"

/* define file */
#define DEF_ADD     (      0.01F )

#define TERGET_SPD  (     100.0F )
#define MAX_CW_DEG  (       0.0F )
#define MAX_CCW_DEG (       0.0F )

#define DEF_TERGET  (       0.0F )
#define K_P_SPD     (       0.0F )
#define K_I_SPD     (       0.0F )
#define K_D_SPD     (       0.0F )
#define K_P_DEG     (       0.0F )
#define K_I_DEG     (       0.0F )
#define K_D_DEG     (       0.0F )

class RunLineCalculator_ohs {
public:
    //生成
    RunLineCalculator_ohs();
    //デストラクタ
    ~RunLineCalculator_ohs();

    void calcRunLine( SENC_CLR color, int8_t* p_speed, int8_t* p_deg );

private:
	/* メンバ */
    int8_t mSpeed;
    int8_t mDeg;
	SENC_CLR mAfterColor;
	SENC_CLR mBeforeColor;
    FLOT mPValue;
    FLOT mIValue;
    FLOT mDValue;

};

#endif  // RUNLINECALCULATOR_OHS_H_
