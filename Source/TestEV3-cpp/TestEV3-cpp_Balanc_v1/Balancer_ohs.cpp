#include "hal_ev3_std.h"
#include "RunningAdmin_ohs.h"
#include "Balancer_ohs.h"

/**
 * コンストラクタ
 */
Balancer_ohs::Balancer_ohs( GyroAdmin_ohs* gyro_admin )
:mGyroAdmin( gyro_admin )
{
    mRightPwm     = 0;
    mLeftPwm      = 0;
    
    balance_init();  // 倒立振子制御初期化
}

/**
 * デストラクタ
 */
Balancer_ohs::~Balancer_ohs() {
}

/**    RunningAdmin_ohs* mRunningAdmin;

 * モータ出力値計算
 */
BOOL Balancer_ohs::calcPWM( int8_t spd, int8_t deg, void* running_admin ) {
    FLOT fGyroValue = 0;
    FLOT fOffSet  = 0;
    FLOT fNowRDeg = 0;
    FLOT fNowLDeg = 0;
    FLOT fBattery = 0;
    RunningAdmin_ohs* RunningAdmin = ( RunningAdmin_ohs* )running_admin;
    //ジャイロ値の取得
    fGyroValue =   ( FLOT )mGyroAdmin->getValue();

    //モータ回転値の取得
    fNowRDeg = ( FLOT )RunningAdmin->isRightRotary();
    fNowLDeg = ( FLOT )RunningAdmin->isLeftRotary();

    //バッテリー残量
    fBattery = ( FLOT )ev3_battery_voltage_mV();

    // 倒立振子制御APIを呼び出し、倒立走行するための
    // 左右モータ出力値を得る
    balance_control(
        static_cast<float>(spd),
        static_cast<float>(deg),
        static_cast<float>( fGyroValue ),
        static_cast<float>( fOffSet ),
        static_cast<float>( fNowLDeg ),
        static_cast<float>( fNowRDeg ),
        static_cast<float>( fBattery ),
        &mLeftPwm,
        &mRightPwm);

        return true;
}

/**
 * モータ出力値計算
 */
int8_t Balancer_ohs::isRightPWM() {
    return ( mRightPwm );
}

/**
 * モータ出力値計算
 */
int8_t Balancer_ohs::isLeftPWM() {
    return ( mLeftPwm );
}