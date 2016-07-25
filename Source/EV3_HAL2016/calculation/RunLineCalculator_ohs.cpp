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

    mPValue = 0;
    mIValue = 0;
    mDValue = 0;

    mKspdP = K_P_SPD;
    mKspdI = K_I_SPD;
    mKspdD = K_D_SPD;
    mKdegP = K_P_DEG;
    mKdegI = K_I_DEG;
    mKdegD = K_D_DEG;
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
    mPValue = fNowDeflect - DEF_TERGET;
    /* 微分値計算 */
    mDValue = fNowDeflect - fOldDeflect;
    /* 積分値計算 */
    mIValue += mDValue;

    /* 走行角度計算 */
    fTempDeg = ( mKdegP * mPValue ) + ( mKdegI * mIValue ) + ( mKdegD * mDValue );
    mDeg = ( int8_t )fTempDeg;

    /* 走行速度計算 */
    if( mIValue < 0 ) { cSpeedRev = -1; }//符号反転用
    fTempSpeed = TERGET_SPD - ( mKspdI  * ( mIValue * cSpeedRev ));
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
           char cSpeedRev  = 1;
           FLOT fCvtRefLv  = 0.0F;
           FLOT fTempSpeed = 0.0F;
           FLOT fSpeedOff  = 0.0F;
           FLOT fTempDeg   = 0.0F;

    //走行パラメータの取得*意味は無い
    mSpeed = *p_speed;
    mDeg   = *p_deg;
    
    /* 反射値の取得 */
    fCvtRefLv = ( FLOT )reflection_lv;
    
    /* 比較値計算 */
    mPValue = TERGET_LV - fCvtRefLv;
    /* 微分値計算 */
    mDValue = mPValue - fOldDevPoint;
    /* 積分値計算 */
    mIValue += mDValue;

    /* 走行角度計算 */
    fTempDeg = ( mKdegP * mPValue ) + ( mKspdI * mIValue ) + ( mKspdD * mDValue );
    mDeg = ( int8_t )fTempDeg;

    /* 走行速度計算 */
    //fTempSpeed = TERGET_SPD - ( K_I_SPD  * ( mIValue * cSpeedRev ));

    fSpeedOff = ( mKspdP * mPValue ) + ( mKspdI * mIValue ) + ( mKspdD * mDValue );
    if( fSpeedOff < 0.0F ) { cSpeedRev = -1; }//符号反転用
    fTempSpeed = TERGET_SPD - ( fSpeedOff * cSpeedRev );

    mSpeed = ( int8_t )fTempSpeed;
    //走行パラメータの返却
    
    *p_speed = mSpeed;
    *p_deg   = mDeg;

    //値の保存
    fOldDevPoint = mPValue;
}

FLOT RunLineCalculator_ohs::isP(void)
{
    return mPValue;
}
FLOT RunLineCalculator_ohs::isI(void)
{
    return mIValue;
}
FLOT RunLineCalculator_ohs::isD(void)
{
    return mDValue;
}

void RunLineCalculator_ohs::setGain( PID_SETTING* p_set_file )
{
if( p_set_file == NULL ) { return; }

    mKspdP = p_set_file->fSpdP;
    mKspdI = p_set_file->fSpdI;
    mKspdD = p_set_file->fSpdD;
    mKdegP = p_set_file->fDegP;
    mKdegI = p_set_file->fDegI;
    mKdegD = p_set_file->fDegD;

    SCHR   cString[100];
    memset( cString , 0, sizeof(cString));

    sprintf(( char* )cString, "[%3.3f]" , mKspdP );
	ev3_lcd_draw_string( cString, 0, 8*1);
    sprintf(( char* )cString, "[%3.3f]" , mKspdI );
	ev3_lcd_draw_string( cString, 0, 8*2);
    sprintf(( char* )cString, "[%3.3f]" , mKspdD );
	ev3_lcd_draw_string( cString, 0, 8*3);
    sprintf(( char* )cString, "[%3.3f]" , mKdegP );
	ev3_lcd_draw_string( cString, 0, 8*4);
    sprintf(( char* )cString, "[%3.3f]" , mKdegI );
	ev3_lcd_draw_string( cString, 0, 8*5);
    sprintf(( char* )cString, "[%3.3f]" , mKdegD );
	ev3_lcd_draw_string( cString, 0, 8*5);

    return;
}
