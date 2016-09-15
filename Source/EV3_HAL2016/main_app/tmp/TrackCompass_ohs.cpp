/* include file */
#include "ev3api.h"
#include "hal_ev3_std.h"
#include "TrackCompass_ohs.h"

/**
* コンストラクタ
*/
TrackCompass_ohs::TrackCompass_ohs( RunningAdmin_ohs* running_admin, RunLineCalculator_ohs* running_line_calculator )
:mRunningAdmin( running_admin ),
 mRunLineCalculator( running_line_calculator ) {
	mReferenceAxis = 0.0F;
	mNowRAxis = 0;
	mTargetDirection = 0;
	mRAxisTurnFinish = false;
}

/**
* デストラクタ
*/
TrackCompass_ohs::~TrackCompass_ohs() {
}

//マップ基軸算出のデータ収集
void TrackCompass_ohs::callReferenceSearch()
{
}

//マップ基軸を現在地で固定
void TrackCompass_ohs::setReferenceAxis() { mNowRAxis = ( int32_t )mReferenceAxis; }

//基軸中心からの指定角回転
BOOL TrackCompass_ohs::callRAxisTurn( int32_t target ) {

	return true;
}

//指定角回転達成確認
BOOL TrackCompass_ohs::getRAxisTurnFinish()
{
	return false;
}

//マップ基軸の取得
int32_t TrackCompass_ohs::getReferenceAxis() { return ( int32_t )mReferenceAxis; }
