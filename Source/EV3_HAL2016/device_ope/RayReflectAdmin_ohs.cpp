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

/* ---------------------------------------------------------------------------------------------- */
// includeファイル
/* ---------------------------------------------------------------------------------------------- */

#include <string.h>				// memset用
#include "hal_ev3_std.h"		// HAL_EV3大会用　標準ヘッダ
#include "RayReflectAdmin_ohs.h"// 光学センサ管理

/* ---------------------------------------------------------------------------------------------- */
// クラス名      : RayReflectAdmin_ohs
// 役割名        : 光学センサ値管理
// 役割概要      : 光学センサにより取得した角速度値のフィルタリング・取得周期管理・
//                状態判別を行う。API「ev3api::ColorSensor」を用いる。
// 作成日        : 2016/07/14  田中　翔吾  新規作成
/* 引数 ----------------------------------------------------------------------------------------- */
// [I N]ev3api::ColorSensor& color_sensor : ev3apiカラーセンサの使用
/* ---------------------------------------------------------------------------------------------- */
RayReflectAdmin_ohs::RayReflectAdmin_ohs( ev3api::ColorSensor& color_sensor )
:mColorSensor(color_sensor)/* 光学センサ値取得用＠コンストラクタ優先処理 */
{
	mNowReflValue = 0;
	mOldReflValue = 0;
	mState = SCLR_BLACK;// 黒線検知で初期化
	
	memset( mQueue, 0, sizeof( mQueue ));
	mQNo = 0;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名    : ~RayReflectAdmin_ohs
// 機能名        : デストラクタ
// 機能概要      : オブジェクトの破棄
// 作成日        : 2016/07/14  田中　翔吾＠新規作成
/* ---------------------------------------------------------------------------------------------- */
RayReflectAdmin_ohs::~RayReflectAdmin_ohs() {}

/* パブリック ----------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名    : callValueUpdate
// 機能名        : 光学センサ値の更新
// 機能概要      : 光学センサ値の取得・キューイング
// 作成日        : 2016/07/14  田中　翔吾＠新規作成
/* ---------------------------------------------------------------------------------------------- */
void RayReflectAdmin_ohs::callValueUpDate( void )
{
	int16_t sBrightness;// 取得反射値一時記録
	static uint16_t cNo = 0;// キューインデックス

	// sBrightness = mColorSensor.getBrightness();	//光学センサの反射値の取得
	sBrightness = getClrCvtBright();// カラー値-＞反射値変換取得

	// 記録キューの更新
	cNo %= R_QUEUE_MAX;
	mQNo = cNo;
	mQueue[mQNo] = sBrightness;
	cNo++;
	
	// ローパスフィルタ
	calcLowPassFilter();

	return;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名    : getValue
// 機能名        : 取得値の出力
// 機能概要      : フィルタリング済みの光学値を出力する
// 作成日        : 2016/07/14  田中　翔吾＠新規作成
/* 戻り値 [int16_t] ----------------------------------------------------------------------------- */
// 範囲指定無し:光学反射値
/* ---------------------------------------------------------------------------------------------- */
int16_t RayReflectAdmin_ohs::getValue( void )
{
	return mNowReflValue;
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名    : getState
// 機能名        : ライン色の取得
// 機能概要      : ライン色を推測する
// 作成日        : 2016/07/14  田中　翔吾＠新規作成
/* 戻り値 [int16_t] ----------------------------------------------------------------------------- */
// 範囲指定無し:光学反射値
/* ---------------------------------------------------------------------------------------------- */
SENC_CLR RayReflectAdmin_ohs::getState( void )
{
	SINT iIdx = 0;
	UINT iWhiteCount = 0;// 白検知カウンタ
	UINT iBlackCount = 0;// 黒検知カウンタ
	UINT iGrayCount  = 0;// 灰検知カウンタ

	/* 中間値範囲チェック ----------------------------------------------------------------------- */
	for( iIdx = 0; iIdx < R_QUEUE_MAX; iIdx++ ) {
		/* 線色カウンタ */
		if( mQueue[iIdx] < THRESHOLD_BLACK ) { iBlackCount++; continue; } 
		if( mQueue[iIdx] > THRESHOLD_WHITE ) { iWhiteCount++; continue; }
		if( mQueue[iIdx] > THRESHOLD_BLACK && mQueue[iIdx] < THRESHOLD_WHITE ) {
			iGrayCount++;
		}
	}

	/* 反射値チェック */
	if( iBlackCount > iGrayCount ) { mState = SCLR_BLACK; } // 状態 : ブラック
	else { mState = SCLR_GRAY; }							// 状態 : グレー
	if( iWhiteCount == R_QUEUE_MAX ){ mState = SCLR_WHITE; }// 状態 : ホワイト
	
	return mState;
}

/* プライベート --------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
// メソッド名    : calcLowPassFilter
// 機能名        : フィルタリング計算
// 機能概要      : 取得した光学センサ値のフィルタリング計算
// 作成日        : 2016/07/14  田中　翔吾＠新規作成
/* ---------------------------------------------------------------------------------------------- */
void RayReflectAdmin_ohs::calcLowPassFilter( void )
{
	FLOT fNowRef  = ( FLOT )mQueue[mQNo] * GAIN_NOW + ( FLOT )mOldReflValue * GAIN_OLD;
	mNowReflValue = ( int16_t )fNowRef;
	mOldReflValue = mNowReflValue;// 反射値を過去反射値に記録
}

/* ---------------------------------------------------------------------------------------------- */
// メソッド名    : getClrCvtBright
// 機能名        : カラー値の反射値変換
// 機能概要      : フルカラーセンサからRGB値を取得し、単純反射値に変換する
// 作成日        : 2016/07/14  田中　翔吾＠新規作成
/* 戻り値 [int16_t] ----------------------------------------------------------------------------- */
// 0 ～ REY_MAX_REF(200):変換後光学反射値
/* ---------------------------------------------------------------------------------------------- */
int16_t RayReflectAdmin_ohs::getClrCvtBright( void )
{
	rgb_raw_t RgbRaw;// RGB値取得用＠ev3api.hより
	FLOT fRed    = 0.0F;// カラーセンサ計測値＠赤
	FLOT fGre    = 0.0F;// カラーセンサ計測値＠緑
	FLOT fBle    = 0.0F;// カラーセンサ計測値＠青
	FLOT fBright = 0.0F;// 変換値

	memset( &RgbRaw, 0, sizeof( RgbRaw ));

	mColorSensor.getRawColor( RgbRaw );// RGB値の取得

	/* 反射値の変換 */
	fRed = ( FLOT )RgbRaw.r;
	fGre = ( FLOT )RgbRaw.g;
	fBle = ( FLOT )RgbRaw.b;
	
	//取得値の合成
	fBright = ( fRed * 0.0F ) + ( fGre * 0.5F )+ ( fBle * 0.5F );
	
	/* 出力範囲補正 */
	if( fBright < 0.0F ) { fBright = 0.0F; }// 最低値カット
	if( fBright > REY_MAX_REF ) { fBright = REY_MAX_REF; }// 上限値カット

#ifdef PRINT/* デバッグ＠LCD表示 */
    SCHR   cString[50];
    memset( cString , 0, sizeof(cString));

	sprintf(( char* )cString, "Sam_Value[%3d]Red_Value[%3d]",(int)fBright,(int)RgbRaw.r);
	ev3_lcd_draw_string( cString, 0, 8*4);
	sprintf(( char* )cString, "Sam_State[%3d]Gre_Value[%3d]",(int)mState,(int)RgbRaw.g);
	ev3_lcd_draw_string( cString, 0, 8*5);
	sprintf(( char* )cString, "              Ble_Value[%3d]",(int)RgbRaw.b);
	ev3_lcd_draw_string( cString, 0, 8*6);
#endif

	return (int16_t)fBright;
}
/* ---------------------------------------------------------------------------------------------- */
/*                          Copyright HAL College of Technology & Design                          */
/* ---------------------------------------------------------------------------------------------- */
