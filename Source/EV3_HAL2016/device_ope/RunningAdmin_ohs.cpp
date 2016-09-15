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

    mFront    = 0;
    mTurn     = 0;
    mTurnOFS  = TURN_OFS;
    
    mBalanceF = false;
    mBrakeF   = true;
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
void RunningAdmin_ohs::postRunning ( int32_t speed, int32_t deg, BOOL balancer, BOOL brake )
{
    mFront    = (int8_t)speed;
    mTurn     = (int8_t)deg;
    mBalanceF = balancer;
    mBrakeF   = brake;
}

//オフセット値設定
bool RunningAdmin_ohs::setTurnOffset ( int8_t offset  )
{
    if(( offset > 5 ) || ( offset > -5 )) { return false; }
    mTurnOFS = offset;
    return true;
}
//オフセット値の返却
int8_t RunningAdmin_ohs::getTurnOffset () { return mTurnOFS; }

/**
 * 走行実行
 */
void RunningAdmin_ohs::callRunning ( )
{
    static FLOT fBrake = BRAKE_INI;
    static FLOT fDiv = 0.0F;
    static int8_t cFrontOld = 0.0F;
    int8_t cFront_    = 0;
    int8_t cRighitOfs = 0;
    int8_t cLeftOfs   = 0;

    //速度ブレーキ制御
    if( mFront != cFrontOld ) { 
        fBrake = BRAKE_INI;
        fDiv = ( FLOT )( mFront - cFrontOld );
        cFrontOld = mFront;
    }
    if( fBrake > BRAKE_MAX ) { fBrake -= BRAKE_ADD; }
    if( mBrakeF ) { cFront_ = mFront - ( int8_t )( fDiv * fBrake ); }
    else { cFront_ = mFront; }

    // バランス制御有無
    if( mBalanceF ) {
        mBalancer->calcPWM( cFront_, mTurn, this );
        mRightPwm = mBalancer->isRightPWM( );
        mLeftPwm  = mBalancer->isLeftPWM( );
    } else {
        mBalancer->init();
        mRightPwm = cFront_ - mTurn;
        mLeftPwm  = cFront_ + mTurn;
    }

    /* オフセット計算 */
    //オフセット値の取得
    if( mTurnOFS > 0  ) {
        cRighitOfs -= mTurnOFS;
    } else {
        cLeftOfs   += mTurnOFS;
    }

    //オフセット
    mRightPwm = mRightPwm + cRighitOfs;
    mLeftPwm  = mLeftPwm  + cLeftOfs;

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
