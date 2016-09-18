/**
 *******************************************************************************
 **	ファイル名 : balancer_param.c
 **
 **	概要       : 倒立振子制御パラメータ
 **
 ** 注記       : 倒立振子制御パラメータは制御特性に大きな影響を与えます。
 **
 *******************************************************************************
 **/

/*============================================================================
 * データ定義
 *===========================================================================*/
float A_D = 0.8F;	/* ローパスフィルタ係数(左右車輪の平均回転角度用) */
float A_R = 0.996F;	/* ローパスフィルタ係数(左右車輪の目標平均回転角度用) */

/* 状態フィードバック係数
 * K_F[0]: 車輪回転角度係数
 * K_F[1]: 車体傾斜角度係数
 * K_F[2]: 車輪回転角速度係数
 * K_F[3]: 車体傾斜角速度係数
 */
float K_F[4] = {-0.870303F, -31.9978F, -1.1566F*0.6, -2.78873F};
float K_I = -0.44721F;   /* サーボ制御用積分フィードバック係数 */

// float K_PHIDOT = 25.0F*2.5F; /* 車体目標旋回角速度係数 */
float K_PHIDOT = 25.0F*2.5F; /* 車体目標旋回角速度係数 */
// float K_THETADOT = 7.5F; /* モータ目標回転角速度係数 */
float K_THETADOT = 10.8F; /* モータ目標回転角速度係数@battery 8200以上 */
// float K_THETADOT = 10.5F; /* モータ目標回転角速度係数@battery 8000以上 */
// float K_THETADOT = 11.0F; /* モータ目標回転角速度係数@battery 8500以上 */
// float K_THETADOT = 8.0F; /* モータ目標回転角速度係数@battery 7500以上 */

const float BATTERY_GAIN = 0.001089F;	/* PWM出力算出用バッテリ電圧補正係数 */
const float BATTERY_OFFSET = 0.625F;	/* PWM出力算出用バッテリ電圧補正オフセット */

/******************************** END OF FILE ********************************/
