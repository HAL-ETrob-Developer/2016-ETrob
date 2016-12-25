/* ---------------------------------------------------------------------------------------------- */
// TrackCompass_ohs.h
// EV3_HAL2016\基本機能\走行路方位探索
// コース上の前半の直線を基軸とした、直進・旋回を管理する。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// TC0001  2016/07/16  大塚　信晶  新規作成
// TC0002  2016/07/18  大塚　信晶  バグフィックス・動作確認
/* ---------------------------------------------------------------------------------------------- */
#ifndef MAINAPP_TRACKCOMPASS_OHS_H_
#define MAINAPP_TRACKCOMPASS_OHS_H_

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include "../device_ope/RunningAdmin_ohs.h"
#include "../calculation/RunLineCalculator_ohs.h"

/* ---------------------------------------------------------------------------------------------- */
// 定数定義
/* ---------------------------------------------------------------------------------------------- */

#define RAT_TRN_MAX		(     1500 )/* 旋回指定範囲 */
#define SND_TRN_MAX		(       50 )/* 最大旋回量 */
#define RA_PK     		(     0.5F )/* 比例制御ゲイン */

#define TC_TOLERANCE	(       10 )/* 目標許容誤差 */

#define RA_STD_SPD		(        0 )/* 基軸旋回＠前進速度（通常0） */
#define RA_ALT_SPD		(       20 )/* 基軸移動＠前進速度_バランス・支え共用 */
#define RA_ALT_RSPD		(      -20 )/* 基軸移動＠後進速度_バランス走行用 */
#define RA_ALT_RT_SPD	(      -10 )/* 基軸移動＠後進速度_尻尾支え走行用 */
#define RA_STD_BRN		(     true )/* 基軸移動時バランス有無 */
#define RA_STD_BRK		(     true )/* 基軸移動時ブレーキ有無 */

#define RA_NOW_GAIN		(     0.1F )/* 基軸探索＠取得値係数 */
#define RA_OLD_GAIN		(     0.9F )/* 基軸探索＠記録値係数 */

/* ---------------------------------------------------------------------------------------------- */
// クラス名     : TrackCompass_ohs
// 役割名       : 走行路方位探索
// 役割概要     : コースの基軸探索、軸中心の移動・旋回
// 作成日       : 2016/07/16  大塚　信晶  新規作成
/* ---------------------------------------------------------------------------------------------- */
class TrackCompass_ohs
{
	public:/* ------------------------------------------------------------------------ パブリック */
		// コンストラクタ
		TrackCompass_ohs( RunningAdmin_ohs* running_admin, RunLineCalculator_ohs* running_line_calculator );
		// デストラクタ
		~TrackCompass_ohs();

		/* メソッド */
		void callReferenceSearch();// マップ基軸算出のデータ収集
		void setReferenceAxis();   // マップ基軸を現在地で固定
		BOOL callRAxisTurn( int32_t target );// 基軸中心からの指定角回転
		BOOL callRAxisMove( int32_t move_length, BOOL balancer );// 指定角回転達成確認地点からの移動
		BOOL getRAxisTurnFinish( int32_t target );// 指定角回転達成確認

	private:/* --------------------------------------------------------------------- プライベート */
		/* メソッド */
		int32_t getReferenceAxis();// マップ基軸の取得
		int8_t calcFollowDegree( int32_t target );// 指定角に沿う出力角度の計算

		/* メンバ */
		RunningAdmin_ohs*      mRunningAdmin;// 走行管理
		RunLineCalculator_ohs* mRunLineCalculator;// 走行線探索

		FLOT    mReferenceAxis;  // 収集中のマップ基軸
		int32_t mNowRAxis;       // 決定後マップ基軸
		int32_t mTargetDirection;// 目標基軸中心旋回角度
		BOOL    mRAxisTurnFinish;// 目標角達成フラグ

};// class TrackCompass_ohs

#endif  // MAINAPP_TRACKCOMPASS_OHS_H_
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
