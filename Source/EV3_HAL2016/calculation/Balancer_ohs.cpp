#include "Balancer_ohs.h"
#include "balancer.h"
#include "ev3api.h"

/**
 * コンストラクタ
 */
Balancer_ohs::Balancer_ohs( RunningAdmin_ohs* running_admin, 
                                GyroAdmin_ohs* gyro_admin )
{
    mRunningAdmin = running_admin;
    mGyroAdmin    = gyro_admin;
    mRightPwm     = 0;
    mLeftPwm      = 0;
}

/**
 * デストラクタ
 */
Balancer_ohs::~Balancer_ohs() {
}

/**
 * モータ出力値計算
 */
BOOL Balancer_ohs::getPWM( int8_t spd, int8_t deg ) {
    FLOT fGyroValue = 0;
    FLOT fOffSet = 0;
    FLOT fNowRDeg = 0;
    FLOT fNowLDeg = 0;
    FLOT fBattery = 0;

    //ジャイロ値の取得
    fGyroValue =   ( FLOT )mGyroAdmin->getValue();

    //モータ回転値の取得
    fNowRDeg = ( FLOT )mRunningAdmin->isRightRotary();
    fNowLDeg = ( FLOT )mRunningAdmin->isLeftRotary();

    //バッテリー残量
    FLOT fBattery = ( FLOT )ev3_battery_voltage_mV();

    // 倒立振子制御APIを呼び出し、倒立走行するための
    // 左右モータ出力値を得る
    balance_control(
        static_cast<float>(spd),
        static_cast<float>(deg),
        fGyroValue,
        fOffSet,
        fNowLDeg,
        fNowRDeg,
        fBattery,
        &mLeftPwm,
        &mRightPwm);

        return true;
}

/**
 * モータ出力値計算
 */
int8_t Balancer_ohs::isRightDeg() {
    return ( mRightPwm );
}

/**
 * モータ出力値計算
 */
int8_t Balancer_ohs::isLeftDeg() {
    return ( mLeftPwm );
}