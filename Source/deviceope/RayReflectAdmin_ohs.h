/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_RAYREFLECTADMIN_OHS_H_
#define DEVICEOPE_RAYREFLECTADMIN_OHS_H_

class RayReflectAdmin_ohs {
public:
    //生成
    RayReflectAdmin_ohs();
    //デストラクタ 死ぬときあるよ
        virtual ~RayReflectAdmin_ohs();

    void callReflectValueUpDate();
    void getReflectValue();
    void getReflectState();


private:

};

#endif  // DEVICEOPE_RAYREFLECTADMIN_OHS_H_
