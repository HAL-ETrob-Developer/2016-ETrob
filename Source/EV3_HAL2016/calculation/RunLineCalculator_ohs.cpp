#include "hal_ev3_std.h"
#include "RunLineCalculator_ohs.h"

/**
 * コンストラクタ
 */
RunLineCalculator_ohs::RunLineCalculator_ohs()
{
	mAfterColor = SCLR_GRAY;
	mBeforeColor = SCLR_GRAY;

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
    static FLOT fNowDeflect = 0;
    static FLOT fOldDeflect = 0;
           char cSpeedRev   = 1;

    //カラーセンサ取得
    mAfterColor = color;
    //走行パラメータの取得*意味は無い
    mSpeed = *p_speed;
    mDeg   = *p_deg;
    
    /* カラーセンサ判別 */
    if( mBeforeColor == mAfterColor ) {
        if( mAfterColor == SCLR_WHITE ) {
            fNowDeflect += DEF_ADD;//目標偏差増減
        } else {
            fNowDeflect -= DEF_ADD;//目標偏差増
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
    mDeg = ( uint8_t )( K_P_DEG * mPValue + K_I_DEG * mIValue + K_D_DEG * mDValue );

    /* 走行速度計算 */
    if( mIValue < 0 ) { cSpeedRev = -1; }//符号反転用
    mSpeed = ( int8_t )( TERGET_SPD - K_I_SPD * ( mIValue * cSpeedRev ));

    //走行パラメータの返却
    *p_speed = mSpeed;
    *p_deg   = mDeg;

    //値の保存
    mBeforeColor = mAfterColor;
    fOldDeflect  = fNowDeflect;
}