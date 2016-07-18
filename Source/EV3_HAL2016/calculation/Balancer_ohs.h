/* by ohs50465 T.UENO */

#ifndef CALCULATION_BALANCER_OHS_H_
#define CALCULATION_BALANCER_OHS_H_

#include "balancer.h"
#include "ev3api.h"
#include "../device_ope/GyroAdmin_ohs.h"

class Balancer_ohs {
public:
    //生成
    Balancer_ohs( GyroAdmin_ohs* gyro_admin );
    //デストラクタ 死ぬときあるよ
    ~Balancer_ohs();

    BOOL calcPWM( int8_t spd, int8_t deg, void* running_admin );
    int8_t isRightPWM( void );
    int8_t isLeftPWM( void );
private:
    GyroAdmin_ohs* mGyroAdmin;
    int8_t mRightPwm;
    int8_t mLeftPwm;
};

#endif  // MAINAPP_BALANCER_OHS_H_
