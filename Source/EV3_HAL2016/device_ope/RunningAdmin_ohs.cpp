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

    mFront = 0;
    mTurn = 0;
    mBalanceF = false;
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

#ifdef PRINT
	char cString[50];
	memset( cString, 0, sizeof( cString ));
	sprintf(( char* )cString, "mRightRotary[%5d]",mRightRotary);
	ev3_lcd_draw_string( cString, 0, 8*9);
	sprintf(( char* )cString, "mRightRotary[%5d]",mLeftRotary);
	ev3_lcd_draw_string( cString, 0, 8*10);
	sprintf(( char* )cString, "mRightPwm[%5d]",mRightPwm);
	ev3_lcd_draw_string( cString, 0, 8*11);
	sprintf(( char* )cString, "mLeftPwm[%5d]",mLeftPwm);
	ev3_lcd_draw_string( cString, 0, 8*12);
#endif
}

/**
 * 走行指示
 */
void RunningAdmin_ohs::postRunning ( int32_t speed, int32_t deg, BOOL balancer )
{
    mFront    = (int8_t)speed;
    mTurn     = (int8_t)deg;
    mBalanceF = balancer;
}

/**
 * 走行実行
 */
void RunningAdmin_ohs::callRunning ( )
{
    // バランス制御有無
    if( mBalanceF ) {
        mBalancer->calcPWM( mFront, mTurn, this );
        mRightPwm = mBalancer->isRightPWM( );
        mLeftPwm  = mBalancer->isLeftPWM( );
    } else {
        mBalancer->init();
        mRightPwm = mFront - mTurn;
        mLeftPwm  = mFront + mTurn;
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
int32_t RunningAdmin_ohs::getAngle ( )
{
    return mLeftRotary - mRightRotary;
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
    return ( mLeftPwm - mRightPwm );
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
