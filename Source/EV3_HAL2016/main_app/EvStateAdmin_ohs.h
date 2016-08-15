/* by ohs50465 T.Ueno */

#ifndef MAINAPP_EVSTATEADMIN_OHS_H_
#define MAINAPP_EVSTATEADMIN_OHS_H_

#include "ev3api.h"
#include "hal_ev3_std.h"

#include "../device_ope/RayReflectAdmin_ohs.h"
#include "../device_ope/GyroAdmin_ohs.h"
#include "../device_ope/RunningAdmin_ohs.h"
#include "../device_ope/TailAdmin_ohs.h"

typedef struct _EV3_STATE{
	SENC_CLR   color;
	GYRO_STATE balance;
	int32_t    mileage;
	int32_t    ev3_deg;
	int32_t    Tail_deg;
}EV3_STATE;

class EvStateAdmin {
public:
	//生成
	BodyStateAdmin();
	//デストラクタ
	~BodyStateAdmin();

	/* 本体状態の回収 */
	void execStateCollection();

	/* 本体状態のリフレッシュ */
	void execStateRefresh();
	
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
	BODY_STATE mNowState;
	BODY_STATE mOldState;
	//メンバ
	RayReflectAdmin_ohs*   mRayReflectAdmin;
	GyroAdmin_ohs*         mGyroAdmin;
	RunningAdmin_ohs*      mRunningAdmin;
	TailAdmin_ohs*         mTailAdmin;
};

#endif  // MAINAPP_EVSTATEADMIN_OHS_H_
