#include "TailAdmin_ohs.h"

/**
 * コンストラクタ
 */
TailAdmin_ohs::TailAdmin_ohs( ev3api::Motor& tailWheel )
{
	mTailDeg = 0;
	mTailTarget = 0;
	mTailWheel = tailWheel;
}

/**
 * デストラクタ
 */
TailAdmin_ohs::~TailAdmin_ohs() {
}

/**
 * 尾角度更新
 */
void TailAdmin_ohs::callTailDegreeUpdate() {
	mTailDeg = mTailWheel.getCount();
}

/**
 * 尾角度指示
 */
BOOL TailAdmin_ohs::postTailDegree( int32_t postTailDeg ) {
	BOOL overflag = false;
	
	mTailTarget = ( postTailDeg - mTailDeg) * GAIN;

	if (mTailTarget > MAX_TARGET){
		mTailTarget = MAX_TARGET;
		overflag = true;
	} else if (mTailTarget < MIN_TARGET){
		mTailTarget = MIN_TARGET;
		overflag = true;
	}

	return (overflag);
}

/**
 * 尾動作実行
 */
void TailAdmin_ohs::callTailDegree() {
	mTailWheel.setPWM(mTailTarget);
}

/**
 * 尾角度取得
 */
int32_t TailAdmin_ohs::getTailDegree() {
	return (mTailWheel);
}