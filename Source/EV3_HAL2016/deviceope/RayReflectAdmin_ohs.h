/* by ohs50465 T.UENO   */
/*    ohs50247 S.TANAKA */

#ifndef DEVICEOPE_RAYREFLECTADMIN_OHS_H_
#define DEVICEOPE_RAYREFLECTADMIN_OHS_H_

#ifndef HAL_EV3_STD_H_
#define HAL_EV3_STD_H_
#include "../hal_ev3_std.h"
#endif	//HAL_EV3_STD_H_

#include <queue>

class RayReflectAdmin_ohs
{
	public:
		/* コンストラクタ ( インスタンス生成時に呼び出される ) */
		RayReflectAdmin_ohs();
		
		/* デストラクタ */
		virtual ~RayReflectAdmin_ohs();

		/* メソッド */
		void 		callValueUpDate( void );		//光学センサ反射値の更新
		int8_t		getValue( void );				//光学センサ反射値の取得
		enum COLOR 	getState( void );				//光学センサの状態の取得

	private:
		/* メンバ */
		int8_t	Brightness;
		enum COLOR	State;
		queue<int8_t> Qu;
		
		/* メソッド */
		void setLowPassFilter( void );				//ローパスフィルタ
};

#endif  // DEVICEOPE_RAYREFLECTADMIN_OHS_H_
