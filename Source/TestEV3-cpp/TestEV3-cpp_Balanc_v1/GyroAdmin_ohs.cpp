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
	memset( &mQueue[0], 0, sizeof( mQueue ));
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
	mNowGyroValue = mGyroSensor.getAnglerVelocity();
	
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
	return mNowGyroValue; 
}

/**
 * ジャイロセンサの状態の取得
 */
GYRO_STATE GyroAdmin_ohs::getState( void )
{
	SINT iIdx = 0;
	int16_t sVelocity;

	//安定値チェック
	for( iIdx = 0; iIdx < QUEUE_MAX; iIdx++){
		if( mQueue[iIdx] < -THRESHOLD_STABILITY || mQueue[iIdx] > THRESHOLD_STABILITY ){
			//ジャイロ値フィルタリング
			sVelocity = mNowGyroValue * GAIN_NOW + mOldGyroValue * GAIN_OLD;

			//転倒検知
			if( sVelocity > THRESHOLD_FALLING || sVelocity < -THRESHOLD_FALLING ){
				/* 状態：転倒 */
				mState = GSTA_FALLING;
			}else{
				/* 状態：不安定 */
				mState = GSTA_UNSTABLE;
			}

			break;
		}		
	}
	/* 状態：安定 */
	if( iIdx == QUEUE_MAX ){ mState = GSTA_STABILITY; }
	
	//ジャイロ値を過去ジャイロ値に記録
	mOldGyroValue = mNowGyroValue;
	
	return mState;
}