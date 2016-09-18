/* by ohs50465 T.UENO */
/*    ohs50247 S.TANAKA */

#ifndef DEVICEOPE_GYRO_ADMIN_OHS_H_
#define DEVICEOPE_GYRO_ADMIN_OHS_H_

#include <string.h>
#include "ev3api.h"
#include "GyroSensor.h"

#define QUEUE_MAX	(  127 )		/* キュー個数 */

/* ゲイン値 */
#define	GYR_GAIN_NOW		( 0.3F )		/* 現在 */
#define	GYR_GAIN_OLD		( 0.7F )		/* 過去 */

/* 閾値 */
#define	THRESHOLD_STABILITY		(    9 )	/* 安定 */
#define	THRESHOLD_UNSTABILITY	(   40 )	/* 不安定 */
#define	THRESHOLD_FALLING		(  200 )	/* 転倒 */

class GyroAdmin_ohs
{
	public:
		/* コンストラクタ ( インスタンス生成時に呼び出される ) */
		GyroAdmin_ohs( ev3api::GyroSensor& gyro_sensor );
		
		/* デストラクタ */
		~GyroAdmin_ohs();

		/* メソッド */
		bool        initDegree();
		void 		callValueUpdate( void );	//ジャイロセンサの値の更新
		void 		callValueUpdateDummy( void );	//ジャイロセンサ異常の為のダミーメソッド＠20160918
		int16_t 	getValue( void );			//ジャイロセンサの値の取得
		int16_t		getFilterValue( void );		//ジャイロセンサの値の取得(フィルタリング)
		GYRO_STATE	getState( void );			//ジャイロセンサ状態の取得

	private:
		/* メンバ */
		ev3api::GyroSensor& mGyroSensor;
		int16_t mNowGyroValue;
		int16_t mOldGyroValue;
		int16_t mVelocity;
		
		int16_t mOffSet;
		GYRO_STATE	mState;
		int16_t mQueue[QUEUE_MAX];
		uint16_t mQNo;
		bool mInit;

};

#endif  // DEVICEOPE_GYROADMIN_OHS_H_
