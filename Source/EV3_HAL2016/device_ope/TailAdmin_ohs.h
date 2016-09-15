/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_TAILADMIN_OHS_H_
#define DEVICEOPE_TAILADMIN_OHS_H_

#include "Motor.h"

#define TIL_P_GAIN		( 0.6F)
#define TIL_I_GAIN		( 0.6F)
#define TIL_D_GAIN		( 10.0F)

#define MAX_TARGET	(  110)
#define MIN_TARGET	(  -10)

#define MAX_VALUE	(  100)
#define MIN_VALUE	( -100)
class TailAdmin_ohs
{
    public:
    //生成
    TailAdmin_ohs( ev3api::Motor& tail_wheel );
    //デストラクタ 死ぬときあるよ
    ~TailAdmin_ohs();

    void callValueUpDate();
	BOOL postTailDegree( int32_t postTailDeg );
    void callActDegree();
    int32_t getTailDegree();
    BOOL setOfsetDegree( int32_t ofset_tail_deg );

	private:
    ev3api::Motor& mTailWheel;
    int32_t mTailDeg;
    int32_t mExecutVal;
    int32_t mTailTarget;
    int32_t mOfsetDeg;
};

#endif  // DEVICEOPE_TAILADMIN_OHS_H_
