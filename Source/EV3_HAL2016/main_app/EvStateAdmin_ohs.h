/* ---------------------------------------------------------------------------------------------- */
// EvStateAdmin_ohs.h
// EV3_HAL2016\基本機能\本体状態管理
// 状態遷移に必要なセンサ値の管理・取得。遷移間の偏差から遷移条件を計測する。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// EV0000  2016/08/03  上野　徹    新規作成
// EV0001  2016/08/16  大塚　信晶  クラス名の変更、コード修正
/* ---------------------------------------------------------------------------------------------- */

#ifndef MAINAPP_EVSTATEADMIN_OHS_H_
#define MAINAPP_EVSTATEADMIN_OHS_H_

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */
#include "ev3api.h"

#include "../device_ope/RayReflectAdmin_ohs.h"
#include "../device_ope/GyroAdmin_ohs.h"
#include "../device_ope/RunningAdmin_ohs.h"
#include "../device_ope/TailAdmin_ohs.h"

/* ---------------------------------------------------------------------------------------------- */
// 構造体定義
/* ---------------------------------------------------------------------------------------------- */
/* 本体状態保持 */
typedef struct _EV3_STATE{
	SENC_CLR   color;
	GYRO_STATE balance;
	int32_t    mileage;
	int32_t    ev3_deg;
	int32_t    Tail_deg;
}EV3_STATE;

/* ---------------------------------------------------------------------------------------------- */
// クラス名     : EvStateAdmin_ohs
// 役割名       : 本体状態管理
// 役割概要     : 本体状態を各クラスから取得し、記録する。状態の切り替わりごとに値を保持し、
//                状態遷移条件を計測する。
// 作成日       : 2016/08/03  上野　徹    新規作成
/* ---------------------------------------------------------------------------------------------- */
class EvStateAdmin_ohs {
    public:/* ------------------------------------------------------------------------ パブリック */
		EvStateAdmin_ohs( RayReflectAdmin_ohs* ray_reflect_admin, GyroAdmin_ohs* gyro_admin, RunningAdmin_ohs* running_admin, TailAdmin_ohs* tail_admin );// コンストラクタ
		~EvStateAdmin_ohs();// デストラクタ

		bool setStateCollection();// 本体状態の回収
		void setStateRefresh();// 本体状態のリフレッシュ
		SENC_CLR getColorSensorState();// カラーセンサ状態取得
		GYRO_STATE getBalanceState();// バランス状態取得
		int32_t getMileage();// 走行距離取得
		int32_t getBodyAngle();// 本体角度取得
		int32_t getTailAngle();// 尾角度取得

    private:/* --------------------------------------------------------------------- プライベート */
		//メンバ
		EV3_STATE mNowState;// 現在（遷移中）の本体状態
		EV3_STATE mOldState;// 遷移前の本体状態記録
		RayReflectAdmin_ohs*   mRayReflectAdmin;// 光学センサ
		GyroAdmin_ohs*         mGyroAdmin;// ジャイロセンサ
		RunningAdmin_ohs*      mRunningAdmin;// 走行値管理
		TailAdmin_ohs*         mTailAdmin;// 尻尾角度

};// class EvStateAdmin_ohs

#endif  // MAINAPP_EVSTATEADMIN_OHS_H_
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
