/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_GYROADMIN_OHS_H_
#define DEVICEOPE_GYROADMIN_OHS_H_

class GyroAdmin_ohs {
public:
    //生成
    GyroAdmin_ohs();
    //デストラクタ 死ぬときあるよ
        virtual ~GyroAdmin_ohs();

    void callGyroUpDate();
    void getValue();
    void getState();


private:

};

#endif  // DEVICEOPE_GYROADMIN_OHS_H_
