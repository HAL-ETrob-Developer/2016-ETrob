#include "hal_ev3_std.h"
#include <string.h>

#include "RunLineCalculator_ohs.h"

/**
 * コンストラクタ
 */
RunLineCalculator_ohs::RunLineCalculator_ohs()
{
    mSpeed  = 0;
    mDeg    = 0;

    mPValue[SPEED_ID] = 0;
    mIValue[SPEED_ID] = 0;
    mDValue[SPEED_ID] = 0;

    mPValue[DEGRE_ID] = 0;
    mIValue[DEGRE_ID] = 0;
    mDValue[DEGRE_ID] = 0;

    mKP[SPEED_ID] = K_P_SPD;
    mKI[SPEED_ID] = K_I_SPD;
    mKD[SPEED_ID] = K_D_SPD;

    mKP[DEGRE_ID] = K_P_DEG;
    mKI[DEGRE_ID] = K_I_DEG;
    mKD[DEGRE_ID] = K_D_DEG;
}

/**
 * デストラクタ
 */
RunLineCalculator_ohs::~RunLineCalculator_ohs() {
}

/**
 * モータ出力値計算
 */
void RunLineCalculator_ohs::calcRunLine( SENC_CLR color, int8_t* p_speed, int8_t* p_deg )
{
	static SENC_CLR AfterColor  = SCLR_GRAY;
	static SENC_CLR BeforeColor = SCLR_GRAY;
    static FLOT fNowDeflect = 0;
    static FLOT fOldDeflect = 0;
           char cSpeedRev   = 1;
           FLOT fTempSpeed  = 0;
           FLOT fTempDeg    = 0;

    //カラーセンサ取得
    AfterColor = color;
    //走行パラメータの取得*意味は無い
    mSpeed = *p_speed;
    mDeg   = *p_deg;
    
    /* カラーセンサ判別 */
    if( BeforeColor == AfterColor ) {
        if( AfterColor == SCLR_WHITE ) {
            fNowDeflect -= DEF_ADD;//目標偏差増減
        } else {
            fNowDeflect += DEF_ADD;//目標偏差増
        }
    } else {
        //偏差プリセット
        fNowDeflect = 0;
    }
    /* 比較値計算 */
    mPValue[0] = fNowDeflect - DEF_TERGET;
    /* 微分値計算 */
    mDValue[0] = fNowDeflect - fOldDeflect;
    /* 積分値計算 */
    mIValue[0] += mDValue[0];

    /* 走行角度計算 */
    fTempDeg = ( mKP[DEGRE_ID] * mPValue[0] ) + ( mKI[DEGRE_ID] * mIValue[0] ) + (   mKD[DEGRE_ID] * mDValue[0] );
    mDeg = ( int8_t )fTempDeg;

    /* 走行速度計算 */
    if( mIValue[0] < 0 ) { cSpeedRev = -1; }//符号反転用
    fTempSpeed = TERGET_SPD - ( mKI[SPEED_ID]  * ( mIValue[0] * cSpeedRev ));
    mSpeed = ( int8_t )fTempSpeed;
    //走行パラメータの返却
    
    *p_speed = mSpeed;
    *p_deg   = mDeg;

    //値の保存
    BeforeColor = AfterColor;
    fOldDeflect  = fNowDeflect;
}

void RunLineCalculator_ohs::calcRunLineUseRefLv( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg )
{
    static FLOT fOldDevPoint  = 0;
    static FLOT fOldEV3Deg    = 0;
           char cSpeedRev  = 1;
           FLOT fCvtRefLv  = 0.0F;
           FLOT fTempSpeed = 0.0F;
           FLOT fSpeedOfS  = 0.0F;
           FLOT fTempDeg   = 0.0F;

    //走行パラメータの取得*意味は無い
    mSpeed = *p_speed;
    mDeg   = *p_deg;
    
    /* 反射値の取得 */
    fCvtRefLv = ( FLOT )reflection_lv;
    
    /* 走行角度計算 ----------------------------------------------------------------------------- */
    
    /* 比較値計算 */
    mPValue[DEGRE_ID] = TERGET_LV - fCvtRefLv;
    /* 微分値計算 */
    mDValue[DEGRE_ID] = mPValue[DEGRE_ID] - fOldDevPoint;
    /* 積分値計算 */
    mIValue[DEGRE_ID] += mDValue[DEGRE_ID];

    /* 走行角度計算 */
    fTempDeg = ( mKP[DEGRE_ID] * mPValue[DEGRE_ID] ) + 
                ( mKI[DEGRE_ID] * mIValue[DEGRE_ID] ) + 
                ( mKD[DEGRE_ID] * mDValue[DEGRE_ID] );
    
    //結果の変換
    mDeg = ( int8_t )fTempDeg;

    //値の保存
    fOldDevPoint = mPValue[DEGRE_ID];

    /* 走行速度計算 ----------------------------------------------------------------------------- */

    /* 比較値計算 */
    mPValue[SPEED_ID] = TERGET_DEG - fTempDeg;
    /* 微分値計算 */
    mDValue[SPEED_ID] = mPValue[SPEED_ID] - fOldEV3Deg;
    /* 積分値計算 */
    mIValue[SPEED_ID] += mDValue[SPEED_ID];

    fSpeedOfS = ( mKP[SPEED_ID] * mPValue[SPEED_ID] ) + 
                ( mKI[SPEED_ID] * mIValue[SPEED_ID] ) + 
                ( mKD[SPEED_ID] * mDValue[SPEED_ID] );
    if( fSpeedOfS < 0.0F ) { cSpeedRev = -1; }//符号反転用
    fTempSpeed = TERGET_SPD - ( fSpeedOfS * cSpeedRev );

    if( T_MIN_SPD > fTempSpeed ){ fTempSpeed = T_MIN_SPD; }

    mSpeed = ( int8_t )fTempSpeed;

    //値の保存
    fOldEV3Deg   = mPValue[SPEED_ID];
    
    //走行パラメータの返却
    *p_speed = mSpeed;
    *p_deg   = mDeg;

    return;
}

FLOT RunLineCalculator_ohs::isP(void)
{
    return mPValue[0];
}
FLOT RunLineCalculator_ohs::isI(void)
{
    return mIValue[0];
}
FLOT RunLineCalculator_ohs::isD(void)
{
    return mDValue[0];
}

void RunLineCalculator_ohs::setGain( PID_SETTING* p_set_file )
{
if( p_set_file == NULL ) { return; }

    mKP[SPEED_ID] = p_set_file->fSpdP;
    mKI[SPEED_ID] = p_set_file->fSpdI;
    mKD[SPEED_ID] = p_set_file->fSpdD;
    mKP[DEGRE_ID] = p_set_file->fDegP;
    mKI[DEGRE_ID] = p_set_file->fDegI;
    mKD[DEGRE_ID] = p_set_file->fDegD;

    SCHR   cString[100];
    memset( cString , 0, sizeof(cString));

    sprintf(( char* )cString, "[%3.3f]" , mKP[SPEED_ID] );
	ev3_lcd_draw_string( cString, 0, 8*1);
    sprintf(( char* )cString, "[%3.3f]" , mKI[SPEED_ID] );
	ev3_lcd_draw_string( cString, 0, 8*2);
    sprintf(( char* )cString, "[%3.3f]" , mKD[SPEED_ID] );
	ev3_lcd_draw_string( cString, 0, 8*3);
    sprintf(( char* )cString, "[%3.3f]" , mKP[DEGRE_ID] );
	ev3_lcd_draw_string( cString, 0, 8*4);
    sprintf(( char* )cString, "[%3.3f]" , mKI[DEGRE_ID] );
	ev3_lcd_draw_string( cString, 0, 8*5);
    sprintf(( char* )cString, "[%3.3f]" , mKD[DEGRE_ID] );
	ev3_lcd_draw_string( cString, 0, 8*5);

    return;
}
