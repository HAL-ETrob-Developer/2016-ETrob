﻿/* ---------------------------------------------------------------------------------------------- */
// TailAdmin_ohs.cpp
// EV3_HAL2016\デバイス制御\尻尾管理
// モータによる尻尾動作。尻尾角の取得管理。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// TL0000  2016/07/14  中嶋　椰真  新規作成
// TL0001  2016/07/14  大塚　信晶  コンパイルチェック単体テスト通過
// TL0002  2016/07/17  大塚　信晶  PID調整
// TL0003  2016/07/19  大塚　信晶  結合テスト通過
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */
#include "ev3api.h"
#include "hal_ev3_std.h"
#include "TailAdmin_ohs.h"

/* ---------------------------------------------------------------------------------------------- */
// クラス名     ：TailAdmin_ohs
// 役割名       ：尻尾モータ管理
// 役割概要     ：尻尾モータへの指示・現在回転量の管理。PID制御を内包する。
// 作成日       ：2016/07/14  中嶋　椰真  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]ev3api::Motor& tail_wheel ：ev3apiモータの使用
/* ---------------------------------------------------------------------------------------------- */
TailAdmin_ohs::TailAdmin_ohs( ev3api::Motor& tail_wheel )
:mTailWheel(tail_wheel)/* 左モータ入出力＠コンストラクタ優先処理 */
{
	mTailDeg    = 0;
	mExecutVal  = 0;
	mTailTarget = 0;
	mOfsetDeg   = 0;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：~TailAdmin_ohs
// 機能名       ：デストラクタ
// 機能概要     ：オブジェクトの破棄
// 作成日       ：2016/07/14  中嶋　椰真  新規作成
/* ---------------------------------------------------------------------------------------------- */
TailAdmin_ohs::~TailAdmin_ohs() {}

/* パブリック ----------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：callValueUpdate
// 機能名       ：モータ回転数の更新
// 機能概要     ：左右モータ回転数の取得
// 作成日       ：2016/07/14  中嶋　椰真  新規作成
/* ---------------------------------------------------------------------------------------------- */
void TailAdmin_ohs::callValueUpDate() {
	mTailDeg = mTailWheel.getCount();// モータ回転値の取得
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：postTailDegree
// 機能名       ：尻尾角指示
// 機能概要     ：尻尾角の指示
// 作成日       ：2016/07/14  中嶋　椰真  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]int32_t post_tail_deg：尻尾角指示＠-10～110
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true :指示角が範囲外
// false:指示値に問題なし
/* ---------------------------------------------------------------------------------------------- */
BOOL TailAdmin_ohs::postTailDegree( int32_t post_tail_deg ) {
	/* 変数宣言 */
	BOOL overflag = false;

	/* 引数チェック＠角度指示範囲のチェック */
	if( MAX_TARGET < post_tail_deg ) { post_tail_deg = MAX_TARGET; overflag = true; }
	if( MIN_TARGET > post_tail_deg ) { post_tail_deg = MIN_TARGET; overflag = true; }

	mTailTarget = post_tail_deg;//角度目標値の登録

	return ( overflag );// 指示範囲チェック結果の返却
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：setOfsetDegree
// 機能名       ：尻尾角オフセットの登録
// 機能概要     ：尻尾角の指示
// 作成日       ：2016/07/14  中嶋　椰真  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]int32_t ofset_tail_deg：オフセット値＠-50～50
/* 戻り値 [BOOL] -------------------------------------------------------------------------------- */
// true :正常終了
// false:引数異常
/* ---------------------------------------------------------------------------------------------- */
BOOL TailAdmin_ohs::setOfsetDegree( int32_t ofset_tail_deg )
{
	/* 引数チェック */
	if(( ofset_tail_deg > 50 ) || ( ofset_tail_deg < -50 )) { return false; }

	mOfsetDeg = ofset_tail_deg;// オフセット登録

	return true;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：callActDegree
// 機能名       ：尻尾動作実行
// 機能概要     ：指定された指示角で尻尾を動作させる。目標角と現在角度に基づき、
//                フィードバック制御にてモータ出力値を決定する。
// 作成日       ：2016/07/14  中嶋　椰真  新規作成
/* ---------------------------------------------------------------------------------------------- */
void TailAdmin_ohs::callActDegree()
{
	/* 変数宣言 --------------------------------------------------------------------------------- */
	static int32_t oldP = 0;// 比例値記録
	static int32_t i    = 0;// 積分記録
	int32_t p = 0;// 比例値
	int32_t d = 0;// 微分値
	
	/* フィードバック計算 ----------------------------------------------------------------------- */
	p = mTailTarget - ( mTailDeg + mOfsetDeg );// 比例計算（オフセット付き）
	d = p - oldP;// 微分計算
	i += d;// 積分計算

	mExecutVal = ( p * TIL_P_GAIN ) + ( i * TIL_I_GAIN ) + ( d * TIL_D_GAIN );// ゲイン

	/* 出力値範囲調整 */
	if (mExecutVal > MAX_VALUE) { mExecutVal = MAX_VALUE; }
	else if ( mExecutVal < MIN_VALUE ) { mExecutVal = MIN_VALUE; }

	oldP = p;// フィードバック用過去値の記録
	
	mTailWheel.setPWM( mExecutVal );// モータ動作実行

	return;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名   ：getTailDegree
// 機能名       ：尻尾角の取得
// 機能概要     ：callValueUpDateメソッド時に記録された尻尾角をオフセット付きで出力する。
// 作成日       ：2016/07/14  中嶋　椰真  新規作成
/* 戻り値 [int32_t] ----------------------------------------------------------------------------- */
// 範囲指定無し :尻尾角度
/* ---------------------------------------------------------------------------------------------- */
int32_t TailAdmin_ohs::getTailDegree() {
	return ( mTailDeg + mOfsetDeg );
}

/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
