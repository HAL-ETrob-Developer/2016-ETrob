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
	int8_t cSendDegree_ = 0;

	//引数チェック
	if(( target > RAT_TRN_MAX ) || ( target < -RAT_TRN_MAX )) { return false; }

	//値の取得
	mTargetDirection = target;

	//走行角度計算
	cSendDegree_ = calcFollowDegree( mTargetDirection );

	//走行指示
	mRunningAdmin->postRunning( RA_STD_SPD, cSendDegree_, RA_STD_BRN, RA_STD_BRK );

	return true;
}

//指定角回転達成確認地点からの移動
BOOL TrackCompass_ohs::callRAxisMove( int32_t move_length, BOOL balancer )
{
	int8_t cSendDegree = 0;
	int8_t cMoveLength = 0;

	/* 走行速度の決定 */
	if( move_length < 0 ) {
		if( balancer ) { cMoveLength = RA_ALT_RSPD; }//後進＠バランス有り
		else { cMoveLength = RA_ALT_RT_SPD; }//後進＠支え走行
	} else { cMoveLength = RA_ALT_SPD; }//前進＠バランス・支え共用

	//走行角度計算
	cSendDegree = calcFollowDegree( mTargetDirection );

	//走行指示
	mRunningAdmin->postRunning( cMoveLength, cSendDegree, balancer, RA_STD_BRK );

	return true;
}



//指定角回転達成確認
BOOL TrackCompass_ohs::getRAxisTurnFinish( int32_t target )
{
	int32_t iCompAngle = 0;//比較用本体方向
	int32_t iNowAngle  = mRunningAdmin->getAngle();;

	//引数チェック
	if(( target > RAT_TRN_MAX ) || ( target < -RAT_TRN_MAX )) { return false; }

	//比較本体角に目標本体角を代入
	iCompAngle = target + mNowRAxis;
	//目標本体角　－　現在本体角　＝　誤差
	iCompAngle = iCompAngle - iNowAngle;

	//目標値達成確認
	if(( TC_TOLERANCE > iCompAngle ) && ( -TC_TOLERANCE < iCompAngle )) {
		mRAxisTurnFinish = true;//達成
	} else {
		mRAxisTurnFinish = false;//未達
	}

	//達成確認
	if( mRAxisTurnFinish ) {
		mRAxisTurnFinish = false;//フラグリセット
		return true;
	}
	return false;
}

//マップ基軸の取得
int32_t TrackCompass_ohs::getReferenceAxis() { return ( int32_t )mReferenceAxis; }

//指定角に沿う出力角度の計算
int8_t TrackCompass_ohs::calcFollowDegree( int32_t target )
{
	FLOT    fSendDegree  = 0.0F;
	FLOT    fTargetDev   = 0.0F;
	FLOT    fNowAngle    = 0.0F;
	int32_t iRetDegree_  = 0;

	//引数チェック
	if(( target > RAT_TRN_MAX ) || ( target < -RAT_TRN_MAX )) { return false; }
	
	fNowAngle = ( FLOT )mRunningAdmin->getAngle();

	//目標角の計算
	fTargetDev = ( FLOT )( target + mNowRAxis );

	//回転出力値の計算
	fSendDegree = fTargetDev - fNowAngle;//現在地と目標値の差分

	//係数付与出力
	iRetDegree_ = ( int32_t )( fSendDegree * RA_PK );

	//指示値範囲チェック
	if( iRetDegree_ < -SND_TRN_MAX ) { iRetDegree_ = -SND_TRN_MAX; }
	else if( iRetDegree_ > SND_TRN_MAX ) { iRetDegree_ = SND_TRN_MAX; }
	
	return ( int8_t )iRetDegree_;
}