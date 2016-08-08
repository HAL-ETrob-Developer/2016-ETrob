#include "ev3api.h"
#include "hal_ev3_std.h"

#include "RunningLineCalculator_ohs.h"

/**
 * コンストラクタ
 */
RunningLineCalculator_ohs::RunningLineCalculator_ohs( BodyStateAdmin_ohs* body_state_admin ) {
:mBodyStateAdmin(body_state_admin)
{
    mColorState = SCLR_GRAY;    
}

/**
 * デストラクタ
 */
RunningLineCalculator_ohs::~RunningLineCalculator_ohs() {
}

/**
 * モータ出力値計算
 */
void RunningLineCalculator_ohs::calcRunningLine() {
    static FLOT mLastColor = GRAY;
    /* 現在カラーセンサ状態の取得 */
    mColorState = mBodyStateAdmin->getColorSensorState;
    /* 前回カラーセンサ状態の確認 */

    /* カラーセンサ判別 */
    if( mColorState == White ) {
        /* 目標偏差増減 */
    
    }
    else {
        /* 目標偏差増 */
    
    }

    /* 比較値計算 */

    /* 微分値計算 */

    /* 走行速度計算 */

    /* 走行角度計算 */

}