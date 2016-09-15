#include "hal_ev3_std.h"
#include "GyroAdmin_ohs.h"


// extern FILE* gBtHandle;//デバッグ用
/**
 * コンストラクタ
 */
GyroAdmin_ohs::GyroAdmin_ohs( ev3api::GyroSensor& gyro_sensor )
:mGyroSensor( gyro_sensor )
{
	mNowGyroValue = 0;
	mOldGyroValue = 0;

	mVelocity = 0;

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

	mNowGyroValue =  mGyroSensor.getAnglerVelocity();
	// mNowGyroValue =  ev3_gyro_sensor_get_rate( EV3_PORT_4 );//実験＠失敗
	mNowGyroValue -= mOffSet;
	

	//記録キューの更新
	mQNo = mQNo % QUEUE_MAX;
	mQueue[mQNo] = mNowGyroValue;
	mQNo++;

	// mGyroSensor.reset();

}

/**
 * ジャイロセンサの値の取得
 */
int16_t GyroAdmin_ohs::getValue( void ) { return mNowGyroValue; }

/**
 * フィルタリングジャイロセンサの値の取得
 */
int16_t GyroAdmin_ohs::getFilterValue( void ) { return mVelocity; }
/**
 * ジャイロセンサの状態の取得
 */
GYRO_STATE GyroAdmin_ohs::getState( void )
{
	SINT iIdx = 0;
	GYRO_STATE	tmpState = GSTA_UNDECIDED;

	//安定値チェック
	for( iIdx = 0; iIdx < QUEUE_MAX; iIdx++){
		if( mQueue[iIdx] < -THRESHOLD_STABILITY || mQueue[iIdx] > THRESHOLD_STABILITY ){
			//ジャイロ値フィルタリング
			mVelocity = ( int16_t )(( FLOT )mNowGyroValue * GYR_GAIN_NOW 
								+ ( FLOT )mOldGyroValue * GYR_GAIN_OLD );
			
			//状態検知
			if( mVelocity > THRESHOLD_FALLING || mVelocity < -THRESHOLD_FALLING ) {
				/* 状態：転倒 */
				tmpState = GSTA_FALLING;
				break;
			}

			if( mVelocity > THRESHOLD_UNSTABILITY || mVelocity < -THRESHOLD_UNSTABILITY ){
				/* 状態：不安定 */
				tmpState = GSTA_UNSTABLE;
				break;
			}

			break;//不定状態
		}		
	}
	/* 状態：安定 */
	if( iIdx == QUEUE_MAX ){ tmpState = GSTA_STABILITY; }

	//ジャイロ値を過去ジャイロ値に記録
	mOldGyroValue = mVelocity;

	return ( mState = tmpState );
}