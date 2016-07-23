#include "hal_ev3_std.h"
#include "RunningAdmin_ohs.h"

/**
 * コンストラクタ
 */
RunningAdmin_ohs::RunningAdmin_ohs( ev3api::Motor& leftwheel, ev3api::Motor& rightwheel,  Balancer_ohs* balancer )
:mLeftWheel( leftwheel ),
 mRightWheel( rightwheel ),
 mBalancer( balancer )
{
    mRightRotary = 0;
    mLeftRotary  = 0;
    mRightPwm    = 0;
    mLeftPwm     = 0;
}

/**
 * デストラクタ
 */
RunningAdmin_ohs::~RunningAdmin_ohs( )
{
}

/**
 * 走行量更新
 */
void RunningAdmin_ohs::callValueUpDate ( )
{
    mRightRotary = mRightWheel.getCount( );
    mLeftRotary  = mLeftWheel.getCount( );
}

/**
 * 走行指示
 */
void RunningAdmin_ohs::postRunning ( int32_t speed, int32_t deg, BOOL baranser )
{
    // バランス制御有無
    if( baranser ) {
        mBalancer->calcPWM( speed, deg, this );
        mRightPwm = mBalancer->isRightPWM( );
        mLeftPwm  = mBalancer->isLeftPWM( );
    } else {
        mRightPwm = speed - deg;
        mLeftPwm  = speed + deg;
    }
    // 消すかも
    if( mRightPwm > PWM_MAX ) {
        mRightPwm = PWM_MAX;
    } else if( mRightPwm < -PWM_MAX ) {
        mRightPwm = -PWM_MAX;
    }
    if( mLeftPwm > PWM_MAX ) {
        mLeftPwm = PWM_MAX;
    } else if( mLeftPwm < -PWM_MAX ) {
        mLeftPwm = -PWM_MAX;
    } // 消すかもここまで
}

/**
 * 走行実行
 */
void RunningAdmin_ohs::callRunning ( )
{
    mRightWheel.setPWM( mRightPwm );            // 右モータ回転
    mLeftWheel.setPWM( mLeftPwm );              // 左モータ回転
}

/**
 * 走行距離取得
 */
int32_t RunningAdmin_ohs::getMileage ( )
{
    return (( mRightRotary + mLeftRotary ) / 2 );
}

/**
 * 走行角度取得
 */
int8_t RunningAdmin_ohs::getAngle ( )
{
    return mRightRotary - mLeftRotary;
}

/**
 * 実指示走行速度取得
 */
int8_t RunningAdmin_ohs::getSpeed ( )
{
    return (( mRightPwm + mLeftPwm ) / 2 );
}

/**
 * 実指示走行角度取得
 */
int8_t RunningAdmin_ohs::getVector ( )
{
    return ( mRightPwm - mLeftPwm );
}

/**
 * 実指示走行角度取得
 */
int32_t RunningAdmin_ohs::isRightRotary ( )
{
    return mRightRotary;
}

int32_t RunningAdmin_ohs::isLeftRotary ( )
{
    return mLeftRotary;
}
