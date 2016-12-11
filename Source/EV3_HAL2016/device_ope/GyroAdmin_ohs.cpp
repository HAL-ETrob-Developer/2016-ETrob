/* ---------------------------------------------------------------------------------------------- */
// GyroAdmin_ohs.cpp
// EV3_HAL2016\デバイス制御\ジャイロセンサ管理
// ジャイロセンサの値取得を管理する。ジャイロセンサの値の取得タイミングは一定でないとならない
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// GR0000  2016/07/14  田中　翔吾  新規作成
// GR0001  2016/07/15  大塚　信晶  コンパイルチェック単体テスト通過
// GR0002  2016/07/19  大塚　信晶  結合テスト通過
// GR0003  2016/09/04  大塚　信晶  バランス状態の追加
// GR0004  2016/09/18  大塚　信晶  ジャイロセンサ異常対策
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */
#include "hal_ev3_std.h"	// HAL_EV3大会用　標準ヘッダ
#include <string.h>			// memset用
#include "GyroAdmin_ohs.h"	// ジャイロセンサ管理

/* ---------------------------------------------------------------------------------------------- */
// グローバル変数使用宣言
/* ---------------------------------------------------------------------------------------------- */
// extern FILE* gBtHandle;//デバッグ用

/* ---------------------------------------------------------------------------------------------- */
// クラス名     ：GyroAdmin_ohs
// 役割名       ：ジャイロセンサ管理
// 役割概要     ：ジャイロセンサにより取得した角速度値のフィルタリング・取得周期管理・
//                状態判別を行う。API「ev3api::GyroSensor」を用いる。
// 作成日       ：2016/07/14  田中　翔吾＠新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]ev3api::GyroSensor& gyro_sensor：ev3apiジャイロセンサーの使用
/* ---------------------------------------------------------------------------------------------- */
GyroAdmin_ohs::GyroAdmin_ohs( ev3api::GyroSensor& gyro_sensor )
:mGyroSensor( gyro_sensor )/* ジャイロ値取得用＠コンストラクタ優先処理 */
{
	mNowGyroValue = 0;// フィルタリング用＠直近値
	mOldGyroValue = 0;// フィルタリング用＠過去値
	mVelocity = 0;// フィルタリング後角速度値
	mOffSet = 0;  // 取得値オフセット＠個体差補正に重要です

	mState  = GSTA_UNDECIDED;// 本体安定度の状態＠不定状態

	memset( mQueue, 0, sizeof( mQueue ));// フィルタリング用キュークリア
	mQNo = 0;// 使用キュー番号を先頭へ

	mInit = false;// 初期化フラグ＠未初期化

	initDegree();// ジャイロセンサイニシャライズ
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：~GyroAdmin_ohs
// 機能名       ：デストラクタ
// 機能概要     ：オブジェクトの破棄
// 作成日       ：2016/07/14  田中　翔吾＠新規作成
/* ---------------------------------------------------------------------------------------------- */
GyroAdmin_ohs::~GyroAdmin_ohs() {}

/* パブリック ----------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：initDegree
// 機能名       ：倒立振子モータ値計算
// 機能概要     ：倒立振子制御に必要なモータ回転数を算出する。＠balancer.cを使用
// 作成日       ：2016/07/15  大塚　信晶＠新規作成
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true  : 初期化完了
// false : 初期化不可
/* ---------------------------------------------------------------------------------------------- */
bool GyroAdmin_ohs::initDegree()
{
	mGyroSensor.reset();// ジャイロ値初期化＠再考の余地あり
	mOffSet = mGyroSensor.getAnglerVelocity();// リセット後の安定値を個体値としてカット値とする
	mInit = true;// 初期化完了
	return mInit;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：callValueUpdateDummy
// 機能名       ：ジャイロセンサの値の更新のダミーメソッド
// 機能概要     ：ジャイロ値更新のON/OFFをIF文を用いずに行う為のメソッド＠app.cpp参照
// 作成日       ：2016/09/18  大塚　信晶＠新規作成
/* ---------------------------------------------------------------------------------------------- */
void GyroAdmin_ohs::callValueUpdateDummy( void ) { return; }

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：callValueUpdate
// 機能名       ：ジャイロセンサの値の更新
// 機能概要     ：ジャイロセンサに値の取得を指示する。
//                このメソッドはタイマ割込みによって呼び出される。
// 作成日       ：2016/07/14  田中　翔吾＠新規作成
/* ---------------------------------------------------------------------------------------------- */
void GyroAdmin_ohs::callValueUpdate( void )
{
	mNowGyroValue =  mGyroSensor.getAnglerVelocity();// 角速度の取得
	// mNowGyroValue =  ev3_gyro_sensor_get_rate( EV3_PORT_4 );//実験＠失敗
	mNowGyroValue -= mOffSet;// カット値補正
	
	// 記録キューの更新
	mQNo = mQNo % QUEUE_MAX;// インクリメントされた値をキュー範囲内へ
	mQueue[mQNo] = mNowGyroValue;// 取得値をキューに格納
	mQNo++;// キューをインクリメント

	// mGyroSensor.reset();//ここにresetを入れてはならないという戒め
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：getValue
// 機能名       ：角速度出力
// 機能概要     ：callValueUpdateメソッドで取得した角速度を出力する。
// 作成日       ：2016/07/14  田中　翔吾＠新規作成
/* 戻り値 [int16_t] ----------------------------------------------------------------------------- */
// 範囲指定無し: 角速度（deg/sec）
/* ---------------------------------------------------------------------------------------------- */
int16_t GyroAdmin_ohs::getValue( void ) { return mNowGyroValue; }

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：getFilterValue
// 機能名       ：フィルタリング付き角速度出力
// 機能概要     ：callValueUpdateメソッドで取得した角速度をフィルタリング後に出力する。
// 作成日       ：2016/07/14  田中　翔吾＠新規作成
/* 戻り値 [int16_t] ----------------------------------------------------------------------------- */
// 範囲指定無し: 角速度（deg/sec）
/* ---------------------------------------------------------------------------------------------- */
int16_t GyroAdmin_ohs::getFilterValue( void ) { return mVelocity; }

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：getState
// 機能名       ：本体安定状態の出力
// 機能概要     ：本体の安定度を状態に分類し出力する
// 作成日       ：2016/07/14  田中　翔吾＠新規作成
/* 戻り値 [GYRO_STATE] -------------------------------------------------------------------------- */
// GSTA_UNDECIDED：不定状態
// GSTA_UNSTABLE ：不安定
// GSTA_STABILITY：安定
// GSTA_FALLING  ：転倒		（hal_ev3_std.hにて定義）
/* ---------------------------------------------------------------------------------------------- */
GYRO_STATE GyroAdmin_ohs::getState( void )
{
	/* ------------------------------------------------------------------------------------------ */
	// 初期処理
	/* ------------------------------------------------------------------------------------------ */
	/* 変数宣言 --------------------------------------------------------------------------------- */
	SINT 		iIdx     = 0;// キューソート用インデックス
	GYRO_STATE	tmpState = GSTA_UNDECIDED;// 状態保存一時領域＠不定状態

	/* ------------------------------------------------------------------------------------------ */
	// 状態判定
	/* ------------------------------------------------------------------------------------------ */
	/* 安定値チェック --------------------------------------------------------------------------- */
	for( iIdx = 0; iIdx < QUEUE_MAX; iIdx++ ) {
		if( mQueue[iIdx] < -THRESHOLD_STABILITY || mQueue[iIdx] > THRESHOLD_STABILITY ) {
			/* 安定状態の範囲外 */

			mVelocity = ( int16_t )(( FLOT )mNowGyroValue * GYR_GAIN_NOW 
								+ ( FLOT )mOldGyroValue * GYR_GAIN_OLD );// ジャイロ値フィルタリング
			/* 状態検知 */
			if( mVelocity > THRESHOLD_FALLING || mVelocity < -THRESHOLD_FALLING ) {
				/* 状態：転倒 */
				tmpState = GSTA_FALLING;// 状態を転倒状態に確定
				break;// 安定値チェックforからbreak
			}
			if( mVelocity > THRESHOLD_UNSTABILITY || mVelocity < -THRESHOLD_UNSTABILITY ){
				/* 状態：不安定 */
				tmpState = GSTA_UNSTABLE;// 状態を不安定状態に確定
				break;// 安定値チェックforからbreak
			}

			break;//不定状態のまま、安定値チェックforからbreak
		}
		/* 安定状態の範囲内 */
	}

	/* 状態：安定＠安定値チェックforを全チェックスルーすれば安定状態で確定 */
	if( iIdx == QUEUE_MAX ){ tmpState = GSTA_STABILITY; }

	//ジャイロ値を過去ジャイロ値に記録
	mOldGyroValue = mVelocity;

	return ( mState = tmpState );// 状態の返却
}
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
