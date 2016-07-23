#include <string.h>
#include "hal_ev3_std.h"

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
	int16_t cBrightness;
	static uint8_t cNo = 0;

	//cBrightness = mColorSensor.getBrightness();	//光学センサの反射値の取得
	cBrightness = getClrCvtBright();

	//記録キューの更新
	cNo %= QUEUE_MAX;
	mQNo = cNo;
	mQueue[mQNo] = cBrightness;
	cNo++;
	
	//ローパスフィルタ
	setLowPassFilter();

}

/**
 * 光学センサの反射値の取得
 */
int16_t RayReflectAdmin_ohs::getValue( void )
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
		if( mQueue[iIdx] < THRESHOLD_BLACK || mQueue[iIdx] > THRESHOLD_WHITE ){
			//反射値チェック
			if( mNowReflValue < THRESHOLD_BLACK ){
				/* 状態：ブラック */
				mState = SCLR_BLACK;
			}else if( mNowReflValue > THRESHOLD_WHITE ){
				/* 状態：ホワイト */
				mState = SCLR_WHITE;
			}	
			break;
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
	FLOT fNowRef  = ( FLOT )mQueue[mQNo] * GAIN_NOW + ( FLOT )mOldReflValue * GAIN_OLD;

	mNowReflValue = ( int16_t )fNowRef;


	//反射値を過去反射値に記録
	mOldReflValue = mNowReflValue;
}

int16_t RayReflectAdmin_ohs::getClrCvtBright( void )
{
	rgb_raw_t RgbRaw;
	memset( &RgbRaw, 0, sizeof(RgbRaw));

	mColorSensor.getRawColor( RgbRaw );

    /* LCD画面表示 */
#ifdef PRINT
    SCHR   cString[50];
    memset( cString , 0, sizeof(cString));

	sprintf(( char* )cString, "Red_Value[%5d]",RgbRaw.r);
	ev3_lcd_draw_string( cString, 0, 8*4);
	sprintf(( char* )cString, "Red_Value[%5d]",RgbRaw.g);
	ev3_lcd_draw_string( cString, 0, 8*5);
	sprintf(( char* )cString, "Red_Value[%5d]",RgbRaw.b);
	ev3_lcd_draw_string( cString, 0, 8*6);
#endif

	return (int16_t)((uint32_t)( RgbRaw.r + RgbRaw.g + RgbRaw.b )/3);
}
