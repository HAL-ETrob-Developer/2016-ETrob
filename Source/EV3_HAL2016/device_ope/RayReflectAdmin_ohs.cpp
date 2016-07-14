#include "RayReflectAdmin_ohs.h"

/**
 * コンストラクタ
 */
RayReflectAdmin_ohs::RayReflectAdmin_ohs( ev3api::ColorSensor& color_sensor )
{
	mColorSensor = color_sensor;
	mNowReflValue = 0;
	mOldReflValue = 0;
	mState = COLOR_BLACK;
	
	memset( mQueue, 0, sizeof( mQueue ) );
	int8_t mQNo = 0;
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
	int8_t cBrightness;
	static int8_t cNo = 0;

	cBrightness = mColorSensor->getBrightness();	//光学センサの反射値の取得

	mQNo = cNo % QUEUE_MAX;
	mQueue[mQNo] = cBrightness;

	setLowPassFilter();

	cNo %= QUEUE_MAX;
	cNo++;
	
}

/**
 * 光学センサの反射値の取得
 */
int8_t RayReflectAdmin_ohs::getValue( void )
{
	return mNowReflValue;
}

/**
 * 光学センサの状態の取得
 */
enum COLOR RayReflectAdmin_ohs::getState( void )
{
	//中間値範囲チェック

	//反射値チェック
	if( mNowReflValue < THRESHOLD_BLACK ){
		/* 状態：ブラック */
		mState = COLOR_BLACK;
	}else if( mNowReflValue > THRESHOLD_WHITE ){
		/* 状態：ブラック */
		mState = COLOR_WHITE;
	}
	return mState;
}

/**
 * ローパスフィルタ
 */
 void setLowPassFilter( void ){
	mNowReflValue = mQueue[mQNo] * GAIN_NOW + mOldReflValue * GAIN_OLD;	
	mOldReflValue = mNowReflValue;
 }
