/* by ohs50465 T.Ueno */

#ifndef MAINAPP_BODYSTATEADMIN_OHS_H_
#define MAINAPP_BODYSTATEADMIN_OHS_H_

#include "../device_ope/RayReflectAdmin_ohs.h"
#include "../device_ope/GyroAdmin_ohs.h"
#include "../device_ope/RunningAdmin_ohs.h"
#include "../device_ope/TailAdmin_ohs.h"

typedef struct {
      int8_t ColorSensorState;
      int16_t BalanceState;
      int32_t Mileage;
      int32_t BodyAngle;
      int32_t TailAngle;
}BODY_STATE;

class BodyStateAdmin {
public:
    //生成
    BodyStateAdmin();
    //デストラクタ
    ~BodyStateAdmin();

    /* 本体状態更新 */
    void setBodyStateUpdate();

    /* カラーセンサ状態取得 */
    SENC_CLR getColorSensorState();

    /* バランス状態取得 */
    GYRO_STATE getBalanceState();

    /* 走行距離取得 */
    int32_t getMileage();

    /* 本体角度取得 */
    int32_t getBodyAngle();

    /* 尾角度取得 */
    int32_t getTailAngle();

private:
    BODY_STATE mNow;
    BODY_STATE mOld;
    //メンバ
    RayReflectAdmin_ohs*   mRayReflectAdmin;
    GyroAdmin_ohs*         mGyroAdmin;
    RunningAdmin_ohs*      mRunningAdmin;
    TailAdmin_ohs*         mTailAdmin;

};

#endif  // MAINAPP_BODYSTATEADMIN_H_
