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
	
	//記録キューの更新
	mQNo = cNo % QUEUE_MAX;
	mQueue[mQNo] = sVelocity;
	cNo %= QUEUE_MAX;
	cNo++;
	
}

/**
 * ジャイロセンサの値の取得
 */
int16_t GyroAdmin_ohs::getValue( void )
{
	mNowGyroValue = mQueue[mQNo];		//現在のキューからジャイロ値を取得
	return mNowGyroValue; 
}

/**
 * ジャイロセンサの状態の取得
 */
 enum GYRO_STATE GyroAdmin_ohs::getState( void )
{
	SINT iIdx = 0;
	
	//安定値チェック
	for(　iIdx = 0; iIdx < QUEUE_MAX; iIdx++){
		if( mQueue[iIdx] < -THRESHOLD_STABILITY && mQueue[iIdx] > THRESHOLD_STABILITY ){
			//ジャイロ値確認
			mNowGyroValue = mQueue[mQNo] * GAIN_NOW + mOldGyroValue * GAIN_OLD;
			if( mNowGyroValue >= THRESHOLD_FALLING || mNowGyroValue <= -THRESHOLD_FALLING ){
				/* 状態：転倒 */
				mState = GSTA_FALLING;
			}else{
				/* 状態：不安定 */
				mState = GSTA_UNSTABLE;
			}
		}		
	}
	
	if( iIdx == QUEUE_MAX ){
		/* 状態：安定 */
		mState = GSTA_STABILITY;
	}
	
	//ジャイロ値を過去ジャイロ値に記録
	mOldGyroValue = mNowGyroValue;
	
	return mState;
}