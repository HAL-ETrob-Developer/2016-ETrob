#include "RayReflectAdmin_ohs.h"

/**
 * コンストラクタ
 */
RayReflectAdmin_ohs::RayReflectAdmin_ohs()
    : m(){
}

/**
 * デストラクタ
 */
RayReflectAdmin_ohs::~RayReflectAdmin_ohs()
{
}

/**
 * 光学センサの反射値の更新
 */
void RayReflectAdmin_ohs::callValueUpdate( void )
{
	Brightness = getBrightness();	//光学センサの反射値の取得
	//記録キューの更新
	Qu.push( Brightness );			//キューに保存
	setLowPassFilter();
}

/**
 * 光学センサの反射値の取得
 */
int8_t RayReflectAdmin_ohs::getValue( void )
{
	Brightness = Qu.pop();
	return Brightness;
}

/**
 * 光学センサの状態の取得
 */
enum COLOR RayReflectAdmin_ohs::getState( void )
{
	return State;
}

/**
 * ローパスフィルタ
 */
 void setLowPassFilter( void ){
 }
