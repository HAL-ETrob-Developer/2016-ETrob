#include "hal_ev3_std.h"
#include "EvStateAdmin_ohs.h"


// extern FILE* gBtHandle;//デバッグ用

/**
 * コンストラクタ
 */
EvStateAdmin_ohs::EvStateAdmin_ohs( RayReflectAdmin_ohs* ray_reflect_admin, GyroAdmin_ohs* gyro_admin, RunningAdmin_ohs* running_admin, TailAdmin_ohs* tail_admin )
:mRayReflectAdmin ( ray_reflect_admin ),
 mGyroAdmin( gyro_admin ),
 mRunningAdmin( running_admin ),
 mTailAdmin( tail_admin ) {

	/* 現本体状態構造体初期化 */
	memset( &mNowState, 0, sizeof( EV3_STATE ));
	/* 旧本体状態構造体初期化 */
	memset( &mOldState, 0, sizeof( EV3_STATE ));
}

/**
 * デストラクタ
 */
EvStateAdmin_ohs::~EvStateAdmin_ohs( ) {
}

/**
 * 本体状態の回収
 */
bool EvStateAdmin_ohs::setStateCollection()
{
	EV3_STATE tmpState;
	memset( &tmpState, 0, sizeof(EV3_STATE));

	/* 一時保存 */
	tmpState.mileage  = mRunningAdmin->getMileage();
	tmpState.ev3_deg  = mRunningAdmin->getAngle();
	tmpState.Tail_deg = mTailAdmin->getTailDegree();
	tmpState.color    = mRayReflectAdmin->getState();
	tmpState.balance  = mGyroAdmin->getState();

	/* 状態の変更確認 ＠未変更＝終了 */
	// if( memcmp( &mNowState, &tmpState, sizeof( EV3_STATE )) == true ) { return false; }
	//レガシーコード
	for( UINT i = 0; i < sizeof( EV3_STATE ); i++ ) {
		if(( *(( UCHR* )(&mNowState) + i )) != ( *(( UCHR* )(&tmpState ) + i ))) { break; }
		if( i == ( sizeof( EV3_STATE ) - 1 )) { return false; }
	}

	/* 本体状態の一斉取得 */
	mNowState.mileage  = tmpState.mileage;
	mNowState.ev3_deg  = tmpState.ev3_deg;
	mNowState.Tail_deg = tmpState.Tail_deg;
	mNowState.color    = tmpState.color;
	mNowState.balance  = tmpState.balance;

#ifdef PRINT
	SCHR   cString[50];
	memset( cString , 0, sizeof(cString));
	sprintf(( char* )cString, "mileage [%6d]",(int)mNowState.mileage);
	ev3_lcd_draw_string( cString, 0, 8*7);
	sprintf(( char* )cString, "ev3_deg [%6d]",(int)mNowState.ev3_deg);
	ev3_lcd_draw_string( cString, 0, 8*8);
	sprintf(( char* )cString, "Tail_deg[%6d]",(int)mNowState.Tail_deg);
	ev3_lcd_draw_string( cString, 0, 8*9);
	sprintf(( char* )cString, "color   [%6d]",(int)mNowState.color);
	ev3_lcd_draw_string( cString, 0, 8*10);
	sprintf(( char* )cString, "balance [%6d]",(int)mNowState.balance);
	ev3_lcd_draw_string( cString, 0, 8*11);
#endif

	return true;
}

/**
 * 相対的な指示に対応する為、状態変更時点の状態を記録する
 */
void EvStateAdmin_ohs::setStateRefresh()
{
	//現在値を過去値へ
	mOldState = mNowState;
}

/**
 * カラーセンサ状態取得
 */
SENC_CLR EvStateAdmin_ohs::getColorSensorState() {
	return mNowState.color;
}

/**
 * バランス状態取得
 */
GYRO_STATE EvStateAdmin_ohs::getBalanceState() {
	return mNowState.balance;
}

/**
 * 走行距離取得
 */
int32_t EvStateAdmin_ohs::getMileage() {
	return ( mNowState.mileage - mOldState.mileage );
}

/**
 * 本体角度取得
 */
int32_t EvStateAdmin_ohs::getBodyAngle() {
	return ( mNowState.ev3_deg - mOldState.ev3_deg );
}

/**
 * 尾角度取得
 */
int32_t EvStateAdmin_ohs::getTailAngle() {
	return mNowState.Tail_deg;
}
