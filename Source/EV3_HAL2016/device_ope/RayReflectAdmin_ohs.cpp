#include <string.h>
#include "ev3api.h"
#include "hal_ev3_std.h"
#include "ColorSensor.h"

#include "RayReflectAdmin_ohs.h"

/**
 * コンストラクタ
 */
RayReflectAdmin_ohs::RayReflectAdmin_ohs( ev3api::ColorSensor& color_sensor )
:mColorSensor(color_sensor)
{
	mNowReflValue = 0;
	mOldReflValue = 0;
	mState = SCLR_BLACK;
	
	memset( mQueue, 0, sizeof( mQueue ) );
	mQNo = 0;
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
void RayReflectAdmin_ohs::callValueUpDate( void )
{
	int8_t cBrightness;
	static int8_t cNo = 0;

	cBrightness = mColorSensor.getBrightness();	//光学センサの反射値の取得
	
	//記録キューの更新
	mQNo = cNo % QUEUE_MAX;
	mQueue[mQNo] = cBrightness;
	cNo %= QUEUE_MAX;
	cNo++;
	
	//ローパスフィルタ
	setLowPassFilter();

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
SENC_CLR RayReflectAdmin_ohs::getState( void )
{
	SINT iIdx = 0;
	
	//中間値範囲チェック
	for( iIdx = 0; iIdx < QUEUE_MAX; iIdx++ ){
		if( mQueue[iIdx] <= THRESHOLD_BLACK || mQueue[iIdx] >= THRESHOLD_WHITE ){
			//反射値チェック
			if( mNowReflValue <= THRESHOLD_BLACK ){
				/* 状態：ブラック */
				mState = SCLR_BLACK;
				break;
			}else if( mNowReflValue >= THRESHOLD_WHITE ){
				/* 状態：ホワイト */
				mState = SCLR_WHITE;
			}	
		}		
	}
	
	if( iIdx == QUEUE_MAX ){
		/* 状態：グレー */
		mState = SCLR_GRAY;
	}
	
	return mState;
}

/**
 * ローパスフィルタ
 */
void RayReflectAdmin_ohs::setLowPassFilter( void )
{
	mNowReflValue = mQueue[mQNo] * GAIN_NOW + mOldReflValue * GAIN_OLD;	
	
	//反射値を過去反射値に記録
	mOldReflValue = mNowReflValue;
}
