#include "RunningAdmin_ohs.h"

/**
 * コンストラクタ
 */
RayReflectAdmin_ohs::RayReflectAdmin_ohs()
    : m() {
}

/**
 * デストラクタ
 */
RayReflectAdmin_ohs::~RayReflectAdmin_ohs() {
}

/**
 * 走行量更新
 */
void RayReflectAdmin_ohs::callRunningValueUpDate() {
	rightRotary=getCount();//右モータ（指定方法がわかりません。）
	leftRotary=getCount();//左モータ（指定方法がわかりません。）
}

/**
 * 走行指示
 */
void RayReflectAdmin_ohs::postRunning() {

}

/**
 * 走行実行
 */
void RayReflectAdmin_ohs::callRunning() {
	setPWM(rightPwm);//右モータ回転
	setPWM(leftPwm);//左モータ回転
}

/**
 * 走行距離取得
 */
void RayReflectAdmin_ohs::getRunningMileage() {
	return ( rightRotary + leftRotary )/2;
}

/**
 * 走行角度取得
 */
void RayReflectAdmin_ohs::getRunningAngle() {
	return ( rightRotary - leftRotary);
}

/**
 * 実指示走行速度取得
 */
void RayReflectAdmin_ohs::getTheRunningPWM() {
	return ( rightPwm + leftPwm ) / 2;
}

/**
 * 実指示走行角度取得
 */
void RayReflectAdmin_ohs::getTheRunningVector() {
	return ( rightPwm - leftPwm );
}
