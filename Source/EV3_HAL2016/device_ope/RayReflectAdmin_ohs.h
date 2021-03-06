/* ---------------------------------------------------------------------------------------------- */
// RayReflectAdmin_ohs.h
// EV3_HAL2016\デバイス制御\光学センサ管理
// 光学センサ値の取得値管理。フィルタリング。状態判断。
/* ---------------------------------------------------------------------------------------------- */
// 番号    日付        氏名        更新履歴
/* ---------------------------------------------------------------------------------------------- */
// RY0000  2016/07/14  田中　翔吾  新規作成
// RY0001  2016/07/15  大塚　信晶  コンパイルチェック単体テスト通過
// RY0002  2016/07/19  大塚　信晶  結合テスト通過
// RY0003  2016/09/16  大塚　信晶  ライン状態の検知制度向上
/* ---------------------------------------------------------------------------------------------- */

#ifndef DEVICEOPE_RAY_REFLECT_ADMIN_OHS_H_
#define DEVICEOPE_RAY_REFLECT_ADMIN_OHS_H_

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include "ev3api.h"     // 大会提供API＠基本ヘッダー
#include "ColorSensor.h"// ev3api : ジャイロセンサ

/* ---------------------------------------------------------------------------------------------- */
// 定数定義
/* ---------------------------------------------------------------------------------------------- */

#define R_QUEUE_MAX		(        200 )	/* キュー個数 */

/* ゲイン値 */
#define GAIN_NOW		(       0.1F )	/* 現在 */
#define GAIN_OLD		(       0.9F )	/* 過去 */

/* 閾値 */
#define	THRESHOLD_BLACK	(         15 )	/* ブラック */
#define	THRESHOLD_WHITE	(         80 )	/* ホワイト */

/* 反射値カット */
#define	REY_MAX_REF		(     200.0F )	/* 最大反射値＠カット */

/* ---------------------------------------------------------------------------------------------- */
// クラス名     : RayReflectAdmin_ohs
// 役割名       : 光学センサ値管理
// 役割概要     : 光学センサにより取得した角速度値のフィルタリング・取得周期管理・
//                状態判別を行う。API「ev3api::ColorSensor」を用いる。
// 作成日       : 2016/07/14  田中　翔吾  新規作成
/* ---------------------------------------------------------------------------------------------- */
class RayReflectAdmin_ohs
{
    public:/* ------------------------------------------------------------------------ パブリック */
		/* コンストラクタ ( インスタンス生成時に呼び出される ) */
		RayReflectAdmin_ohs( ev3api::ColorSensor& color_sensor );
		
		/* デストラクタ */
		~RayReflectAdmin_ohs();

		/* メソッド */
		void callValueUpDate( void );// 光学センサ反射値の更新
		int16_t getValue( void );	 // 光学センサ反射値の取得
		SENC_CLR getState( void );	 // ライン色の取得
	
    private:/* --------------------------------------------------------------------- プライベート */
		/* メンバ */
		ev3api::ColorSensor& mColorSensor;// ev3apiカラーセンサ
		int16_t	mNowReflValue;// フィルタリング用＠直近値
		int16_t mOldReflValue;// フィルタリング用＠過去値
		SENC_CLR mState;// 検知状態
		int16_t mQueue[R_QUEUE_MAX];// フィルタリング用値保持領域
		uint16_t mQNo;// キュー使用位置

		/* メソッド */
		void    calcLowPassFilter( void );//ローパスフィルタ
		int16_t getClrCvtBright( void );  //カラーセンサ

};// class RayReflectAdmin_ohs

#endif  // DEVICEOPE_RAYREFLECTADMIN_OHS_H_
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
