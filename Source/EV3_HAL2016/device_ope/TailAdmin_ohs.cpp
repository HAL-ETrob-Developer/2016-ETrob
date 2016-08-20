#include "ev3api.h"
#include "hal_ev3_std.h"
#include "TailAdmin_ohs.h"

/**
 * コンストラクタ
 */
TailAdmin_ohs::TailAdmin_ohs( ev3api::Motor& tail_wheel )
:mTailWheel(tail_wheel)
{
	mTailDeg    = 0;
	mExecutVal  = 0;
	mTailTarget = 0;
}

/**
 * デストラクタ
 */
TailAdmin_ohs::~TailAdmin_ohs() {
}

/**
 * 尾角度更新
 */
void TailAdmin_ohs::callValueUpDate() {
	mTailDeg = mTailWheel.getCount();
}

/**
 * 尾角度指示
 */
BOOL TailAdmin_ohs::postTailDegree( int32_t post_tail_deg ) {
	BOOL overflag = false;

	//角度指定範囲のチェック
	if( MAX_TARGET < post_tail_deg ) { post_tail_deg = MAX_TARGET; overflag = true; }
	if( MIN_TARGET > post_tail_deg ) { post_tail_deg = MIN_TARGET; overflag = true; }

	//角度目標値の登録
	mTailTarget = post_tail_deg;

	return ( overflag );
}

/**
 * 尾動作実行
 */
void TailAdmin_ohs::callActDegree()
{
	static int32_t oldP = 0;
	static int32_t i    = 0;
	int32_t p = 0;
	int32_t d = 0;
	
	p = mTailTarget - mTailDeg;
	d = p - oldP;
	i += d;

	mExecutVal = ( p * TIL_P_GAIN ) + ( i * TIL_I_GAIN ) + ( d * TIL_D_GAIN );

	if (mExecutVal > MAX_VALUE){ mExecutVal = MAX_VALUE; }
	else if ( mExecutVal < MIN_VALUE ) { mExecutVal = MIN_VALUE; }

	oldP = p;
	
	mTailWheel.setPWM( mExecutVal );
}

/**
 * 尾角度取得
 */
int32_t TailAdmin_ohs::getTailDegree() {
	return ( mTailDeg );
}