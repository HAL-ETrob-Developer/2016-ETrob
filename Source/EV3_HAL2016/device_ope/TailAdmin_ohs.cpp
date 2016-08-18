#include "ev3api.h"
#include "hal_ev3_std.h"
#include "TailAdmin_ohs.h"

/**
 * コンストラクタ
 */
TailAdmin_ohs::TailAdmin_ohs( ev3api::Motor& tail_wheel )
:mTailWheel(tail_wheel)
{
	//mTailWheel  = tail_wheel;
	mTailDeg    = 0;
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
	static int32_t oldP = 0;
	static int32_t i    = 0;
	int32_t p = 0;
	int32_t d = 0;
	BOOL overflag = false;
	
	
	p = post_tail_deg - mTailDeg;
	d = p - oldP;
	i += d;

	mTailTarget = ( p * TIL_P_GAIN ) + ( i * TIL_I_GAIN ) + ( d * TIL_D_GAIN );

	if (mTailTarget > MAX_TARGET){
		mTailTarget = MAX_TARGET;
		overflag = true;
	} else if ( mTailTarget < MIN_TARGET ) {
		mTailTarget = MIN_TARGET;
		overflag = true;
	}

	oldP = p;
	return (overflag);
}

/**
 * 尾動作実行
 */
void TailAdmin_ohs::callActDegree() {
	mTailWheel.setPWM( mTailTarget );
}

/**
 * 尾角度取得
 */
int32_t TailAdmin_ohs::getTailDegree() {
	return ( mTailDeg );
}