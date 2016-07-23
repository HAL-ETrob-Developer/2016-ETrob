#include "hal_ev3_std.h"
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
    fTempDeg = ( K_P_DEG * mPValue ) + ( K_I_DEG * mIValue ) + ( K_D_DEG * mDValue );
    mDeg = ( int8_t )fTempDeg;

    /* 走行速度計算 */
    if( mIValue < 0 ) { cSpeedRev = -1; }//符号反転用
    fTempSpeed = TERGET_SPD - ( K_I_SPD  * ( mIValue * cSpeedRev ));
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
           FLOT fCvtRefLv  = 0;
           FLOT fTempSpeed = 0;
           FLOT fTempDeg   = 0;

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
    fTempDeg = ( K_P_DEG * mPValue ) + ( K_I_DEG * mIValue ) + ( K_D_DEG * mDValue );
    mDeg = ( int8_t )fTempDeg;

    /* 走行速度計算 */
    if( mIValue < 0 ) { cSpeedRev = -1; }//符号反転用
    fTempSpeed = TERGET_SPD - ( K_I_SPD  * ( mIValue * cSpeedRev ));
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