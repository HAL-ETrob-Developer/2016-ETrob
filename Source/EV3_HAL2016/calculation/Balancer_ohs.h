/* by ohs50465 T.UENO */

#ifndef CALCULATION_BALANCER_OHS_H_
#define CALCULATION_BALANCER_OHS_H_

class Balancer_ohs {
public:
    //生成
    Balancer_ohs();
    //デストラクタ 死ぬときあるよ
    ~Balancer_ohs();

    BOOL calcPWM( int8_t spd, int8_t deg );
    int8_t isRightDeg( void );
    int8_t isLeftDeg( void );
private:
    RunningAdmin_ohs* mRunningAdmin;
    GyroAdmin_ohs* mGyroAdmin;
    int8_t mRightPwm;
    int8_t mLeftPwm;


};

#endif  // MAINAPP_BALANCER_OHS_H_
