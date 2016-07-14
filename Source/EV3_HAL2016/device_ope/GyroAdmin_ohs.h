/* by ohs50465 T.UENO */
/*    ohs50247 S.TANAKA */

#ifndef DEVICEOPE_GYRO_ADMIN_OHS_H_
#define DEVICEOPE_GYRO_ADMIN_OHS_H_

#include <string.h>
#include "../hal_ev3_std.h"

#define QUEUE_MAX	(  127 )		/* キュー個数 */

/* ゲイン値 */
#define	GAIN_NOW		( 0.1F )		/* 現在 */
#define	GAIN_OLD		( 0.9F )		/* 過去 */

/* 閾値 */
#define	THRESHOLD_STABILITY		(  50 )		/* 安定 */
#define	THRESHOLD_FALLING		(  300 )	/* 転倒 */

class GyroAdmin_ohs
{
	public:
		/* コンストラクタ ( インスタンス生成時に呼び出される ) */
		GyroAdmin_ohs();
		
		/* デストラクタ */
		~GyroAdmin_ohs();

		/* メソッド */
		void 			callValueUpdate( void );		//ジャイロセンサの値の更新
		int16_t 		getValue( void );				//ジャイロセンサの値の取得
		enum GYRO_STATE	getState( void );				//ジャイロセンサ状態の取得

	private:
		/* メンバ */
		ev3api::GyroSensor& mGyroSensor;
		int16_t mNowGyroValue;
		int16_t mOldGyroValue;
		enum GYRO_STATE	mState;
		int8_t mQueue[QUEUE_MAX];
		int8_t mQNo;

};

#endif  // DEVICEOPE_GYROADMIN_OHS_H_
