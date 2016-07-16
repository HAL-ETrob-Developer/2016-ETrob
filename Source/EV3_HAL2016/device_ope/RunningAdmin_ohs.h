/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_RUNNINGADMIN_OHS_H_
#define DEVICEOPE_RUNNINGADMIN_OHS_H_
#define PWM_MAX ( 100 )
class RunningAdmin_ohs {
public:
    // 生成
    RunningAdmin_ohs( );
    // デストラクタ 死ぬときあるよ
    virtual ~RunningAdmin_ohs( );

    void    callRunningValueUpDate ( );
    void    postRunning ( int32_t speed, int32_t deg, BOOL baranser );
    void    callRunning ( );
    void    getRunningMileage ( );
    void    getRunningAngle ( );
    void    getTheRunningPWM ( );
    void    getTheRunningVector ( );
    int32_t isRightRotary ( );
    int32_t isLeftRotary ( );

private:
    int32_t        mRightRotary;
    int32_t        mLeftRotary;
    int8_t         mRightPwm;
    int8_t         mLeftPwm;
    ev3api::Motor &mLeftWheel;
    ev3api::Motor &mRightWheel;
    Baranser_ohs  *mBaranser;
};

#endif                                          // DEVICEOPE_RUNNINGADMIN_OHS_H_
