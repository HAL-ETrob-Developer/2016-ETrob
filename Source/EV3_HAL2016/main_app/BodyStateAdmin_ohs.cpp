#include "ev3api.h"
#include "hal_ev3_std.h"
#include "BodyStateAdmin_ohs.h"

/**
 * コンストラクタ
 */
BodyStateAdmin_ohs::BodyStateAdmin_ohs(RayReflectAdmin_ohs* ray_reflect_admin, GyroAdmin_ohs* gyro_admin, RunningAdmin_ohs* running_admin, TailAdmin_ohs* tail_admin )
{
        /* 現本体状態構造体初期化 */
        memset( mNow, 0, sizeof( BODY_STATE ) ;
        /* 旧本体状態構造体初期化 */
        memset( mOld, 0, sizeof( BODY_STATE ) );

        mRayReflectAdmin = ray_reflect_admin;
        mGyroAdmin       = gyro_admin;
        mRunningAdmin    = running_admin;
        mTailAdmin       = tail_admin;
}

/**
 * デストラクタ
 */
BodyStateAdmin_ohs::~BodyStateAdmin_ohs( ) {
}

/**
 * 本体状態更新
 */
void BodyStateAdmin_ohs::setBodyStateUpdate() {
    mOld.ColorSensorState = mNow.ColorSensorState;
    mOld.BalanceState = mNow.BalanceState;
    mOld.Mileage = mNow.Mileage;
    mOld.BodyAngle = mNow.BodyAngle;
    mOld.TailAngle = mNow.TailAngle;

    mNow.ColorSensorState = mRayReflectAdmin -> getState();
    mNow.BalanceState = mGyroAdmin -> getState();
    mNow.Milage = mRunningAdmin -> getMileage();
    mNow.BodyAngle = mRunningAdmin -> getAngle();
    mNow.TailAngle = mTailAdmin -> getTailDegree();
}

/**
 * カラーセンサ状態取得
 */
SENC_CLR BodyStateAdmin_ohs::getColorSensorState() {
  return mNow.ColorSensorState;
}

/**
 * バランス状態取得
 */
GYRO_STATE BodyStateAdmin_ohs::getBalanceState() {
  return mNow.BalanceState;
}

/**
 * 走行距離取得
 */
int32_t BodyStateAdmin_ohs::getMileage() {
  return mNow.Milage;
}

/**
 * 本体角度取得
 */
int32_t BodyStateAdmin_ohs::getBodyAngle() {
  return mNow.BodyAngle;
}

/**
 * 尾角度取得
 */
int32_t BodyStateAdmin_ohs::getTailAngle() {
  return mNow.TailAngle;
}
