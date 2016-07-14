/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_RUNNINGADMIN_OHS_H_
#define DEVICEOPE_RUNNINGADMIN_OHS_H_

class RunningAdmin_ohs {
public:
    //生成
    RunningAdmin_ohs();
    //デストラクタ 死ぬときあるよ
        virtual ~RunningAdmin_ohs();

    void callRunningValueUpDate();
    void postRunning();
    void callRunning();
    void getRunningMileage();
    void getRunningAngle();
    void getTheRunningPWM();
    void getTheRunningVector();
    int32_t isRightRotary();
    int32_t isLeftRotary();

private:
	int32_t mRightRotary;
	int32_t mLeftRotary;
	int32_t mRightPwm;
	int32_t mLeftPwm;
};

#endif  // DEVICEOPE_RUNNINGADMIN_OHS_H_
