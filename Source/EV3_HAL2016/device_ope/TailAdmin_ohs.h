﻿/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_TAILADMIN_OHS_H_
#define DEVICEOPE_TAILADMIN_OHS_H_

#include "Motor.h"

#define TIL_P_GAIN		( 0.3F)
#define TIL_I_GAIN		( 1.5F)
#define TIL_D_GAIN		( 5.0F)
#define MAX_TARGET	(  100)
#define MIN_TARGET	( -100)

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


	private:
    ev3api::Motor& mTailWheel;
    int32_t mTailDeg;
    SINT mTailTarget;
};

#endif  // DEVICEOPE_TAILADMIN_OHS_H_
