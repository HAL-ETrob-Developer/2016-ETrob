/* by ohs50465 T.UENO   */
/*    ohs50247 S.TANAKA */

#ifndef DEVICEOPE_RAY_REFLECT_ADMIN_OHS_H_
#define DEVICEOPE_RAY_REFLECT_ADMIN_OHS_H_

#include <string.h>
#include "../hal_ev3_std.h"

#define QUEUE_MAX	(  127 )		/* キュー個数 */	

/* ゲイン値 */
#define GAIN_NOW	( 0.1F )		/* 現在 */
#define GAIN_OLD	( 0.9F )		/* 過去 */

/* 閾値 */
#define	THRESHOLD_BLACK	( 20 )		/* ブラック */
#define	THRESHOLD_WHITE	( 40 )		/* ホワイト */

class RayReflectAdmin_ohs
{
	public:
		/* コンストラクタ ( インスタンス生成時に呼び出される ) */
		RayReflectAdmin_ohs();
		
		/* デストラクタ */
		~RayReflectAdmin_ohs();

		/* メソッド */
		void 		callValueUpDate( void );		//光学センサ反射値の更新
		int8_t		getValue( void );				//光学センサ反射値の取得
		enum COLOR 	getState( void );				//光学センサの状態の取得

	private:
		/* メンバ */
		ev3api::ColorSensor& mColorSensor;
		int8_t	mNowReflValue;
		int8_t 	mOldReflValue;
		enum COLOR	mState;
		int8_t mQueue[QUEUE_MAX];
		int8_t mQNo;
		
		/* メソッド */
		void setLowPassFilter( void );				//ローパスフィルタ
};

#endif  // DEVICEOPE_RAYREFLECTADMIN_OHS_H_
