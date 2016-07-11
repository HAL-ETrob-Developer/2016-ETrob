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

private:

};

#endif  // DEVICEOPE_RUNNINGADMIN_OHS_H_
