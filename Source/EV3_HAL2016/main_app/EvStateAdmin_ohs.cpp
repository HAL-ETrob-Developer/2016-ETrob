#include "hal_ev3_std.h"
#include "EvStateAdmin_ohs.h"

/**
 * コンストラクタ
 */
EvStateAdmin_ohs::EvStateAdmin_ohs( RayReflectAdmin_ohs* ray_reflect_admin, GyroAdmin_ohs* gyro_admin, RunningAdmin_ohs* running_admin, TailAdmin_ohs* tail_admin )
:mRayReflectAdmin ( ray_reflect_admin ),
 mGyroAdmin( gyro_admin ),
 mRunningAdmin( running_admin ),
 mTailAdmin( tail_admin ) {

	/* 現本体状態構造体初期化 */
	memset( &mNowState, 0, sizeof( EV3_STATE ));
	/* 旧本体状態構造体初期化 */
	memset( &mOldState, 0, sizeof( EV3_STATE ));
}

/**
 * デストラクタ
 */
EvStateAdmin_ohs::~EvStateAdmin_ohs( ) {
}

/**
 * 本体状態の回収
 */
void EvStateAdmin_ohs::execStateCollection()
{
	/* 本体状態の一斉取得 */
	mNowState.color    = mRayReflectAdmin->getState();
	mNowState.balance  = mGyroAdmin->getState();
	mNowState.mileage  = mRunningAdmin->getMileage();
	mNowState.ev3_deg  = mRunningAdmin->getAngle();
	mNowState.Tail_deg = mTailAdmin->getTailDegree();
}

/**
 * 相対的な指示に対応する為、状態変更時点の状態を記録する
 */
void EvStateAdmin_ohs::execStateRefresh()
{
	//現在値を過去値へ
	mOldState = mNowState;
}

/**
 * カラーセンサ状態取得
 */
SENC_CLR EvStateAdmin_ohs::getColorSensorState() {
	return mNowState.color;
}

/**
 * バランス状態取得
 */
GYRO_STATE EvStateAdmin_ohs::getBalanceState() {
	return mNowState.balance;
}

/**
 * 走行距離取得
 */
int32_t EvStateAdmin_ohs::getMileage() {
	return ( mNowState.mileage - mOldState.mileage );
}

/**
 * 本体角度取得
 */
int32_t EvStateAdmin_ohs::getBodyAngle() {
	return ( mNowState.ev3_deg - mOldState.ev3_deg );
}

/**
 * 尾角度取得
 */
int32_t EvStateAdmin_ohs::getTailAngle() {
	return mNowState.Tail_deg;
}
