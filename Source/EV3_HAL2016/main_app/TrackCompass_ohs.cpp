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
	FLOT fAngle_    = ( FLOT )mRunningAdmin->getAngle();
	FLOT fOldRAxis_ = mReferenceAxis;
	if( mRunLineCalculator->getDeg() == 0 ) { return; }
	mReferenceAxis = ( fAngle_ * RA_NOW_GAIN ) + ( fOldRAxis_ * RA_OLD_GAIN );
	return;
}

//マップ基軸を現在地で固定
void TrackCompass_ohs::setReferenceAxis() { mNowRAxis = ( int32_t )mReferenceAxis; }

//基軸中心からの指定角回転
BOOL TrackCompass_ohs::callRAxisTurn( int32_t target ) {
	FLOT    fSendDegree  = 0.0F;
	FLOT    fTargetDev   = 0.0F;
	FLOT    fNowAngle    = 0.0F;
	int32_t iSendDegree_ = 0;

	//引数チェック
	if(( target > RAT_TRN_MAX ) || ( target < RAT_TRN_MAX )) { return false; }

	//値の取得
	mTargetDirection = target;
	fNowAngle = ( FLOT )mRunningAdmin->getAngle();

	//目標角の計算
	fTargetDev = ( FLOT )( mTargetDirection + mNowRAxis );

	//回転出力値の計算
	fSendDegree = fTargetDev - fNowAngle;//現在地と目標値の差分
	iSendDegree_ = ( int32_t )( fSendDegree * RA_PK );//係数付与

	//指示値範囲チェック
	if( iSendDegree_ < -SND_TRN_MAX ) { iSendDegree_ = -SND_TRN_MAX; }
	else if( iSendDegree_ > SND_TRN_MAX ) { iSendDegree_ = SND_TRN_MAX; }

	//走行指示
	mRunningAdmin->postRunning( RA_STD_SPD, ( int8_t )iSendDegree_, RA_STD_BRN, RA_STD_BRK );

	//目標値達成確認
	if( 0 == ( int32_t )fSendDegree ) { mRAxisTurnFinish = true; }

	return true;
}

//指定角回転達成確認
BOOL TrackCompass_ohs::getRAxisTurnFinish()
{
	if( mRAxisTurnFinish ) {
		mRAxisTurnFinish = false;
		return true;
	}
	return false;
}

//マップ基軸の取得
int32_t TrackCompass_ohs::getReferenceAxis() { return ( int32_t )mReferenceAxis; }
