/* by ohs50465 T.UENO */
#ifndef DEVICEOPE_RUNNINGADMIN_OHS_H_
#define DEVICEOPE_RUNNINGADMIN_OHS_H_

#include "ev3api.h"
#include "Motor.h"
#include "Balancer_ohs.h"

#define PWM_MAX ( 100 )
class RunningAdmin_ohs
{
public:
    // 生成
    RunningAdmin_ohs( ev3api::Motor& leftwheel, ev3api::Motor& rightwheel, Balancer_ohs* balanser );
    // デストラクタ 死ぬときあるよ
    ~RunningAdmin_ohs( );

    void    callValueUpDate ( );
    void    postRunning ( int32_t speed, int32_t deg, BOOL baranser );
    void    callRunning ( );
    int32_t    getMileage ( );
    int8_t    getAngle ( );
    int8_t    getSpeed ( );
    int8_t    getVector ( );
    int32_t isRightRotary ( );
    int32_t isLeftRotary ( );

private:
    int32_t        mRightRotary;
    int32_t        mLeftRotary;
    int8_t         mRightPwm;
    int8_t         mLeftPwm;
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    Balancer_ohs*  mBalancer;
};

#endif// DEVICEOPE_RUNNINGADMIN_OHS_H_
