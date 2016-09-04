#include "hal_ev3_std.h"
#include "GyroAdmin_ohs.h"

/**
 * コンストラクタ
 */
GyroAdmin_ohs::GyroAdmin_ohs( ev3api::GyroSensor& gyro_sensor )
:mGyroSensor( gyro_sensor )
{
	mNowGyroValue = 0;
	mOldGyroValue = 0;
	mOffSet = 0;
	mState = GSTA_UNDECIDED;

	memset( mQueue, 0, sizeof( mQueue ));
	mQNo = 0;

	mInit = false;

	initDegree();
}

/**
 * デストラクタ
 */
GyroAdmin_ohs::~GyroAdmin_ohs()
{
}
bool GyroAdmin_ohs::initDegree()
{
	mInit = true;
	mGyroSensor.reset();
	mOffSet = mGyroSensor.getAnglerVelocity();
	return mInit;
}

/**
 * ジャイロセンサの値の更新
 */
void GyroAdmin_ohs::callValueUpdate( void )
{
	mNowGyroValue = ( mGyroSensor.getAnglerVelocity()) - mOffSet;
	
	//記録キューの更新
	mQNo = mQNo % QUEUE_MAX;
	mQueue[mQNo] = mNowGyroValue;
	mQNo++;
}

/**
 * ジャイロセンサの値の取得
 */
int16_t GyroAdmin_ohs::getValue( void )
{
#ifdef PRINT
	char cString[50];
	memset( cString, 0, sizeof( cString ));
	sprintf(( char* )cString, "GyroAdmin_ohs::getValue[%5d]",mNowGyroValue);
	ev3_lcd_draw_string( cString, 0, 8*8);
#endif
	return mNowGyroValue; 
}

/**
 * ジャイロセンサの状態の取得
 */
GYRO_STATE GyroAdmin_ohs::getState( void )
{
	SINT iIdx = 0;
	int16_t sVelocity;
	GYRO_STATE	tmpState = GSTA_UNDECIDED;

	//安定値チェック
	for( iIdx = 0; iIdx < QUEUE_MAX; iIdx++){
		if( mQueue[iIdx] < -THRESHOLD_STABILITY || mQueue[iIdx] > THRESHOLD_STABILITY ){
			//ジャイロ値フィルタリング
			sVelocity = mNowGyroValue * GYR_GAIN_NOW + mOldGyroValue * GYR_GAIN_OLD;

			//状態検知
			if( sVelocity > THRESHOLD_FALLING || sVelocity < -THRESHOLD_FALLING ) {
				/* 状態：転倒 */
				tmpState = GSTA_FALLING;
			}
			if( sVelocity > THRESHOLD_UNSTABILITY || sVelocity < -THRESHOLD_UNSTABILITY ){
				/* 状態：不安定 */
				tmpState = GSTA_UNSTABLE;
			}

			break;
		}		
	}
	/* 状態：安定 */
	if( iIdx == QUEUE_MAX ){ tmpState = GSTA_STABILITY; }
	
	//ジャイロ値を過去ジャイロ値に記録
	mOldGyroValue = mNowGyroValue;
	
	return ( mState = tmpState );
}