#include "hal_ev3_std.h"
#include <string.h>

#include "RunLineCalculator_ohs.h"

/**
 * コンストラクタ
 */
RunLineCalculator_ohs::RunLineCalculator_ohs()
{
    mInitF = false;
    mSpeed  = 0;
    mDeg    = 0;
    mOffsetRef = OFFSET_REF;

    memset( mPidGainF, 0, sizeof( mPidGainF ));

    mTergetSoeed[NORMAL_ID] = TERGET_SPD;
    mTergetSoeed[SCRCH__ID] = TERGET_SPD_S;

    mTergetRefLV[NORMAL_ID] = TERGET_LV;
    mTergetRefLV[SCRCH__ID] = TERGET_LV_S;

    mKP[SPEED_ID] = K_P_SPD;
    mKI[SPEED_ID] = K_I_SPD;
    mKD[SPEED_ID] = K_D_SPD;

    mKP[DEGRE_ID] = K_P_DEG;
    mKI[DEGRE_ID] = K_I_DEG;
    mKD[DEGRE_ID] = K_D_DEG;

    mKP[SPEED_ID_S] = K_P_SPD_S;
    mKI[SPEED_ID_S] = K_I_SPD_S;
    mKD[SPEED_ID_S] = K_D_SPD_S;

    mKP[DEGRE_ID_S] = K_P_DEG_S;
    mKI[DEGRE_ID_S] = K_I_DEG_S;
    mKD[DEGRE_ID_S] = K_D_DEG_S;

    setParametersInit();
}

/**
 * デストラクタ
 */
RunLineCalculator_ohs::~RunLineCalculator_ohs() {
}

//パラメータの初期化
void RunLineCalculator_ohs::setParametersInit()
{
    mPValue[SPEED_ID] = 0.0F;
    mIValue[SPEED_ID] = 0.0F;
    mDValue[SPEED_ID] = 0.0F;

    mPValue[DEGRE_ID] = 0.0F;
    mIValue[DEGRE_ID] = 0.0F;
    mDValue[DEGRE_ID] = 0.0F;

    mPValue[SPEED_ID_S] = 0.0F;
    mIValue[SPEED_ID_S] = 0.0F;
    mDValue[SPEED_ID_S] = 0.0F;

    mPValue[DEGRE_ID_S] = 0.0F;
    mIValue[DEGRE_ID_S] = 0.0F;
    mDValue[DEGRE_ID_S] = 0.0F;

    mInitF = true;
}

/**
 * モータ出力値計算
 */
BOOL RunLineCalculator_ohs::calcRunLine( BOOL speed_trac, SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg )
{
    BOOL CenterF = false;
    reflection_lv += mOffsetRef;
    
    if( speed_trac ) { calcRunLineSpeedLine( reflection_lv, p_speed, p_deg); }
    else{ calcRunLineUseRefLv( reflection_lv, p_speed, p_deg); }

    //中央値ならtrue
	if((int)mDeg == 0 ) { CenterF = true; }

    return CenterF;
}


//ライン計算通常PID制御
void RunLineCalculator_ohs::calcRunLineUseRefLv( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg )
{
    static FLOT fOldDevPoint  = 0;
    static FLOT fOldEV3Deg    = 0;
           char cSpeedRev  = 1;
           FLOT fCvtRefLv  = 0.0F;
           FLOT fTempSpeed = 0.0F;
           FLOT fSpeedOfS  = 0.0F;
           FLOT fTempDeg   = 0.0F;

    //イニットフラグのクリア
    mInitF = false;

    //走行パラメータの取得*意味は無い
    mSpeed = *p_speed;
    mDeg   = *p_deg;
    
    /* 反射値の取得 */
    fCvtRefLv = ( FLOT )reflection_lv;
    
    /* 走行角度計算 ----------------------------------------------------------------------------- */
    
    /* 比較値計算 */
    mPValue[DEGRE_ID] = mTergetRefLV[NORMAL_ID] - fCvtRefLv;
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
    fTempSpeed = mTergetSoeed[NORMAL_ID] - ( fSpeedOfS * cSpeedRev );

    if( T_MIN_SPD > fTempSpeed ){ fTempSpeed = T_MIN_SPD; }

    mSpeed = ( int8_t )fTempSpeed;

    //値の保存
    fOldEV3Deg   = mPValue[SPEED_ID];
    
    //走行パラメータの返却
    *p_speed = mSpeed;
    *p_deg   = mDeg;

    return;
}
//ライン探索用
void RunLineCalculator_ohs::calcRunLineSpeedLine( SSHT reflection_lv, int8_t* p_speed, int8_t* p_deg ) 
{
    static FLOT fOldDevPoint  = 0.0F;
    static FLOT fOldEV3Deg    = 0.0F;
           char cSpeedRev  = 1;
           FLOT fCvtRefLv  = 0.0F;
           FLOT fTempSpeed = 0.0F;
           FLOT fSpeedOfS  = 0.0F;
           FLOT fTempDeg   = 0.0F;

    //イニットフラグのクリア
    mInitF = false;

    //走行パラメータの取得*意味は無い
    mSpeed = *p_speed;
    mDeg   = *p_deg;
    
    /* 反射値の取得 */
    fCvtRefLv = ( FLOT )reflection_lv;
    
    /* 走行角度計算 ----------------------------------------------------------------------------- */
    /* 比較値計算 */
    mPValue[DEGRE_ID_S] = mTergetRefLV[SCRCH__ID] - fCvtRefLv;
    /* 微分値計算 */
    mDValue[DEGRE_ID_S] = mPValue[DEGRE_ID_S] - fOldDevPoint;
    /* 積分値計算 */
    mIValue[DEGRE_ID_S] += mDValue[DEGRE_ID_S];

    /* 走行角度計算 */
    fTempDeg = ( mKP[DEGRE_ID_S] * mPValue[DEGRE_ID_S] ) + 
                ( mKI[DEGRE_ID_S] * mIValue[DEGRE_ID_S] ) + 
                ( mKD[DEGRE_ID_S] * mDValue[DEGRE_ID_S] );
    
    //結果の変換
    mDeg = ( int8_t )fTempDeg;

    //値の保存
    fOldDevPoint = mPValue[DEGRE_ID_S];

    /* 走行速度計算 ----------------------------------------------------------------------------- */
    /* 比較値計算 */
    mPValue[SPEED_ID_S] = TERGET_DEG - fTempDeg;
    /* 微分値計算 */
    mDValue[SPEED_ID_S] = mPValue[SPEED_ID_S] - fOldEV3Deg;
    /* 積分値計算 */
    mIValue[SPEED_ID_S] += mDValue[SPEED_ID_S];

    fSpeedOfS = ( mKP[SPEED_ID_S] * mPValue[SPEED_ID_S] ) + 
                ( mKI[SPEED_ID_S] * mIValue[SPEED_ID_S] ) + 
                ( mKD[SPEED_ID_S] * mDValue[SPEED_ID_S] );
    if( fSpeedOfS < 0.0F ) { cSpeedRev = -1; }//符号反転用
    fTempSpeed = mTergetSoeed[SCRCH__ID] - ( fSpeedOfS * cSpeedRev );

    if( T_MIN_SPD > fTempSpeed ){ fTempSpeed = T_MIN_SPD; }

    mSpeed = ( int8_t )fTempSpeed;

    //値の保存
    fOldEV3Deg   = mPValue[SPEED_ID_S];
    
    //走行パラメータの返却
    *p_speed = mSpeed;
    *p_deg   = mDeg;

    return;
}

int8_t RunLineCalculator_ohs::getDeg() { return mDeg; }

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

    memcpy( &mPidGainF[NORMAL_ID], p_set_file, sizeof( mPidGainF ));

    //ライン計算通常PID制御
    mTergetSoeed[NORMAL_ID] = ( p_set_file + NORMAL_ID )->fTerSpeed;
    mTergetRefLV[NORMAL_ID] = ( p_set_file + NORMAL_ID )->fTerRefLv;
    mKP[SPEED_ID]   = ( p_set_file + NORMAL_ID )->fSpdP;
    mKI[SPEED_ID]   = ( p_set_file + NORMAL_ID )->fSpdI;
    mKD[SPEED_ID]   = ( p_set_file + NORMAL_ID )->fSpdD;
    mKP[DEGRE_ID]   = ( p_set_file + NORMAL_ID )->fDegP;
    mKI[DEGRE_ID]   = ( p_set_file + NORMAL_ID )->fDegI;
    mKD[DEGRE_ID]   = ( p_set_file + NORMAL_ID )->fDegD;

    //ライン探索用
    mTergetSoeed[SCRCH__ID] = ( p_set_file + SCRCH__ID )->fTerSpeed;
    mTergetRefLV[SCRCH__ID] = ( p_set_file + SCRCH__ID )->fTerRefLv;
    mKP[SPEED_ID_S] = ( p_set_file + SCRCH__ID )->fSpdP;
    mKI[SPEED_ID_S] = ( p_set_file + SCRCH__ID )->fSpdI;
    mKD[SPEED_ID_S] = ( p_set_file + SCRCH__ID )->fSpdD;
    mKP[DEGRE_ID_S] = ( p_set_file + SCRCH__ID )->fDegP;
    mKI[DEGRE_ID_S] = ( p_set_file + SCRCH__ID )->fDegI;
    mKD[DEGRE_ID_S] = ( p_set_file + SCRCH__ID )->fDegD;
        
    return;
}

PID_SETTING* RunLineCalculator_ohs::isGain( void )
{
    return ( mPidGainF );
}

//オフセット設定
BOOL RunLineCalculator_ohs::setOffsetREf( int16_t RefOffset )
{
    if(( RefOffset > 100 ) || ( RefOffset > -100 )) { return false; }
    mOffsetRef = RefOffset;
    return true;
}
