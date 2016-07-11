/* by ohs50465 T.Ueno */

#ifndef MAINAPP_BODYSTATEADMIN_OHS_H_
#define MAINAPP_BODYSTATEADMIN_OHS_H_

class BodyStateAdmin {
public:
    //生成
    BodyStateAdmin();
    //デストラクタ 死ぬときあるよ
        virtual ~BodyStateAdmin();

    void setBodyStateUpDate();
    void getColorSensorState();
    void getBalanceState();
    void getMileage();
    void getBodyAngle();
    void getTailAngle();

private:

};

#endif  // MAINAPP_BODYSTATEADMIN_H_
