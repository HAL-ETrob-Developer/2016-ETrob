/* by ohs50465 T.UENO */
#ifndef DEVICEOPE_RUNNINGADMIN_OHS_H_
#define DEVICEOPE_RUNNINGADMIN_OHS_H_

#include "ev3api.h"
#include "Motor.h"
#include "../calculation/Balancer_ohs.h"

#define BRAKE_INI ( 0.8F )
#define BRAKE_MAX ( 0.001F )
#define BRAKE_ADD ( 0.001F )
#define PWM_MAX ( 100 )
#define TURN_OFS ( 0 )

class RunningAdmin_ohs
{
public:
    // 生成
    RunningAdmin_ohs( ev3api::Motor& leftwheel, ev3api::Motor& rightwheel, Balancer_ohs* balanser );
    // デストラクタ 死ぬときあるよ
    ~RunningAdmin_ohs( );

    void    callValueUpDate ( );
    void    postRunning ( int32_t speed, int32_t deg, BOOL balancer, BOOL brake );
    void    callRunning ( );
    int32_t getMileage ( );
    int32_t getAngle ( );
    int8_t  getSpeed ( );
    int8_t  getVector ( );
    int32_t isRightRotary ( );
    int32_t isLeftRotary ( );

    //デバッグ用
    bool    setTurnOffset ( int8_t offset  );
    int8_t  getTurnOffset ();

private:
    int32_t mRightRotary;
    int32_t mLeftRotary;
    int8_t  mRightPwm;
    int8_t  mLeftPwm;

    int8_t  mFront;
    int8_t  mTurn;
    int8_t  mTurnOFS;
    BOOL    mBalanceF;
    BOOL    mBrakeF;

    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    Balancer_ohs*  mBalancer;
};

#endif// DEVICEOPE_RUNNINGADMIN_OHS_H_
