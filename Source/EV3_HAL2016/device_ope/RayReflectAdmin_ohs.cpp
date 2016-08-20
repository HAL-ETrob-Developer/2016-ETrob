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
	int16_t sBrightness;
	static uint16_t cNo = 0;

	//sBrightness = mColorSensor.getBrightness();	//光学センサの反射値の取得
	sBrightness = getClrCvtBright();

	//記録キューの更新
	cNo %= R_QUEUE_MAX;
	mQNo = cNo;
	mQueue[mQNo] = sBrightness;
	cNo++;
	
	//ローパスフィルタ
	calcLowPassFilter();

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
	UINT iWhiteCount = 0;
	UINT iBlackCount = 0;
	UINT iGrayCount  = 0;

	//中間値範囲チェック
	for( iIdx = 0; iIdx < R_QUEUE_MAX; iIdx++ ){
		if( mQueue[iIdx] < THRESHOLD_BLACK ) { iBlackCount++; } 
		if( mQueue[iIdx] > THRESHOLD_WHITE ) { iWhiteCount++; }
		if( mQueue[iIdx] < THRESHOLD_BLACK || mQueue[iIdx] > THRESHOLD_WHITE ) {
			iGrayCount++;
		}
	}
	//反射値チェック
	if( iBlackCount > 0 ){
		/* 状態：ブラック */
		mState = SCLR_BLACK;
	} else {
		/* 状態：グレー */
		mState = SCLR_GRAY;
	}
	
	if( iWhiteCount == R_QUEUE_MAX ){
		/* 状態：ホワイト */
		mState = SCLR_WHITE;
	}
	
	return mState;
}


/**
 * ローパスフィルタ
 */
void RayReflectAdmin_ohs::calcLowPassFilter( void )
{
	FLOT fNowRef  = ( FLOT )mQueue[mQNo] * GAIN_NOW + ( FLOT )mOldReflValue * GAIN_OLD;

	mNowReflValue = ( int16_t )fNowRef;


	//反射値を過去反射値に記録
	mOldReflValue = mNowReflValue;
}

int16_t RayReflectAdmin_ohs::getClrCvtBright( void )
{
	rgb_raw_t RgbRaw;
	int32_t sBright = 0;
	memset( &RgbRaw, 0, sizeof(RgbRaw));

	mColorSensor.getRawColor( RgbRaw );
	/* 反射値の変換 */
	sBright = RgbRaw.r + RgbRaw.g + RgbRaw.b;
	if( sBright == 0 ) { sBright = 0; }
	else { sBright = sBright / 3; }
	if( sBright > REY_MAX_REF ) { sBright = REY_MAX_REF; }
    /* LCD画面表示 */
#ifdef PRINT
    SCHR   cString[50];
    memset( cString , 0, sizeof(cString));

	sprintf(( char* )cString, "Sam_Value[%3d]Red_Value[%3d]",(int)sBright,(int)RgbRaw.r);
	ev3_lcd_draw_string( cString, 0, 8*4);
	sprintf(( char* )cString, "Sam_State[%3d]Gre_Value[%3d]",(int)mState,(int)RgbRaw.g);
	ev3_lcd_draw_string( cString, 0, 8*5);
	sprintf(( char* )cString, "              Ble_Value[%3d]",(int)RgbRaw.b);
	ev3_lcd_draw_string( cString, 0, 8*6);
#endif

	return (int16_t)sBright;
}
