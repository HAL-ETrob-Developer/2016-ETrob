#include "GyroAdmin_ohs.h"

/**
 * コンストラクタ
 */
GyroAdmin_ohs::GyroAdmin_ohs( ev3api::GyroSensor& gyro_sensor )
{
	mGyroSensor = gyro_sensor;
	mNowGyroValue = 0;
	mOldGyroValue = 0;
	
	memset( mQueue, 0, sizeof( mQueue ) );
	int8_t mQNo = 0;
	
	
}

/**
 * デストラクタ
 */
GyroAdmin_ohs::~GyroAdmin_ohs()
{
}

/**
 * ジャイロセンサの値の更新
 */
void GyroAdmin_ohs::callValueUpdate( void )
{
	int16_t sVelocity;
	static int8_t cNo = 0;
	
	sVelocity = mGyroSensor->getAnglerVelocity();
	
	mQNo = cNo % QUEUE_MAX;
	mQueue[mQNo] = mNowGyrolValue;
	cNo %= QUEUE_MAX;
	cNo++;
	
}

/**
 * ジャイロセンサの値の取得
 */
int16_t GyroAdmin_ohs::getValue( void )
{
	mNowGyroValue = mQueue[mQNo];
	return mNowGyroValue; 
}

/**
 * ジャイロセンサの状態の取得
 */
 enum GYRO_STATE GyroAdmin_ohs::getState( void )
{
	//安定値チェック

	mNowGyroValue = mQueue[mQNo] * GAIN_NOW + mOldGyroValue * GAIN_OLD;
	
	//ジャイロ値確認
	if( mNowGyroValue >= THRESHOLD ){
		mState = GSTA_FALLING;
	}else{
		mState = GSTA_UNSTABLE;
	}
	
	mOldGyroValue = mNowGyroValue;
	
	return mNowGyroValue;
}