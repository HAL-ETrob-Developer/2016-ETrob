#include "RunningAdmin_ohs.h"

/**
 * コンストラクタ
 */
RayReflectAdmin_ohs::RayReflectAdmin_ohs(   ev3api::Motor &leftwheel,
                                            ev3api::Motor &rightwheel,
                                            Baranser_ohs  *baranser )
    : mLeftWheel( leftwheel ),
    mRightWheel( rightwheel ),
    mBaranser( baranser )
{
    mRightRotary = 0;
    mLeftRotary  = 0;
    mRightPwm    = 0;
    mLeftPwm     = 0;
}

/**
 * デストラクタ
 */
RayReflectAdmin_ohs::~RayReflectAdmin_ohs( )
{
}

/**
 * 走行量更新
 */
void RayReflectAdmin_ohs::callRunningValueUpDate ( )
{
    mRightRotary = mRightWheel.getCount( );
    mLeftRotary  = mLeftWheel.getCount( );
}

/**
 * 走行指示
 */
void RayReflectAdmin_ohs::postRunning ( int32_t speed, int32_t deg, BOOL baranser )
{
    // バランス制御有無
    if( baranser ) {
        mBaranser->calcPWM( speed, deg );
        mRightPwm = Baranser->isRightPWM( );
        mLeftPwm  = Baranser->isLeftPWM( );
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
void RayReflectAdmin_ohs::callRunning ( )
{
    mRightWheel.setPWM( mRightPwm );            // 右モータ回転
    mLeftWheel.setPWM( mLeftPwm );              // 左モータ回転
}

/**
 * 走行距離取得
 */
void RayReflectAdmin_ohs::getRunningMileage ( )
{
    return ( mRightRotary + mLeftRotary ) / 2;
}

/**
 * 走行角度取得
 */
void RayReflectAdmin_ohs::getRunningAngle ( )
{
    return mRightRotary - mLeftRotary;
}

/**
 * 実指示走行速度取得
 */
void RayReflectAdmin_ohs::getTheRunningPWM ( )
{
    return ( mRightPwm + mLeftPwm ) / 2;
}

/**
 * 実指示走行角度取得
 */
void RayReflectAdmin_ohs::getTheRunningVector ( )
{
    return mRightPwm - mLeftPwm;
}

/**
 * 実指示走行角度取得
 */
void RunningAdmin_ohs::isRightRotary ( )
{
    return mRightRotary;
}

void RunningAdmin_ohs::isLeftRotary ( )
{
    return mLeftRotary;
}
