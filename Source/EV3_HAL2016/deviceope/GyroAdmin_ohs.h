/* by ohs50465 T.UENO */
/*    ohs50247 S.TANAKA */

#ifndef DEVICEOPE_GYROADMIN_OHS_H_
#define DEVICEOPE_GYROADMIN_OHS_H_

#ifndef HAL_EV3_STD_H_
#define HAL_EV3_STD_H_
#include "../hal_ev3_std.h"
#endif	//HAL_EV3_STD_H_

class GyroAdmin_ohs
{
	public:
		/* コンストラクタ ( インスタンス生成時に呼び出される ) */
		GyroAdmin_ohs();
		
		/* デストラクタ */
		virtual ~GyroAdmin_ohs();

		/* メソッド */
		void 			callValueUpdate( void );		//ジャイロセンサの値の更新
		int16_t 		getValue( void );				//ジャイロセンサの値の取得
		enum GYRO_STATE	getState( void );				//ジャイロセンサ状態の取得

	private:

};

#endif  // DEVICEOPE_GYROADMIN_OHS_H_
