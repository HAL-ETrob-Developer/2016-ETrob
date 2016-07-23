/* by ohs50465 T.UENO   */
/*    ohs50247 S.TANAKA */

#ifndef DEVICEOPE_RAY_REFLECT_ADMIN_OHS_H_
#define DEVICEOPE_RAY_REFLECT_ADMIN_OHS_H_

#include "ev3api.h"
#include "ColorSensor.h"

#define QUEUE_MAX	(  127 )		/* キュー個数 */	

/* ゲイン値 */
#define GAIN_NOW	( 0.1F )		/* 現在 */
#define GAIN_OLD	( 0.9F )		/* 過去 */

/* 閾値 */
#define	THRESHOLD_BLACK	( 30 )		/* ブラック */
#define	THRESHOLD_WHITE	( 70 )		/* ホワイト */

class RayReflectAdmin_ohs
{
	public:
		/* コンストラクタ ( インスタンス生成時に呼び出される ) */
		RayReflectAdmin_ohs( ev3api::ColorSensor& color_sensor );
		
		/* デストラクタ */
		~RayReflectAdmin_ohs();

		/* メソッド */
		void callValueUpDate( void );		//光学センサ反射値の更新
		int16_t getValue( void );				//光学センサ反射値の取得
		SENC_CLR getState( void );			//光学センサの状態の取得
	
	private:
		/* メンバ */
		ev3api::ColorSensor& mColorSensor;
		int16_t	mNowReflValue;
		int16_t 	mOldReflValue;
		SENC_CLR mState;
		int16_t mQueue[QUEUE_MAX];
		uint8_t mQNo;

		/* メソッド */
		void   setLowPassFilter( void );				//ローパスフィルタ
		int16_t getClrCvtBright( void );				//カラーセンサ
};

#endif  // DEVICEOPE_RAYREFLECTADMIN_OHS_H_
