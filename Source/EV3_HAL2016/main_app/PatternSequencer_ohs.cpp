/* include file */
#include "hal_ev3_std.h"
#include "PatternSequencer_ohs.h"

/**
 * コンストラクタ
 */
PatternSequencer_ohs::PatternSequencer_ohs( RunningAdmin_ohs* running_admin, TailAdmin_ohs* tail_admin )
    : m() {

      /* 現本体状態構造体初期化 */
      memset( ActionIndex, 0, sizeof( RUNNING_PAT_INDEX ) ;

      mRunningAdmin    = running_admin;
      mTailAdmin       = tail_admin;

}

/**
 * デストラクタ
 */
PatternSequencer_ohs::~PatternSequencer_ohs() {
}

/**
 * 定量走行指揮
 */
BOOL PatternSequencer_ohs::callPatternRunning( UCHR InputNumber ) {

/* 走行指示 と 尾角度指示 を行う ----------------------------------------------- */

  /* 走行指示 */
  mRunningAdmin -> postRunning ( ActionIndex[InputNumber].RunningSpeed, ActionIndex[InputNumber].RunningAngle, ActionIndex[InputNumber].Balance );

  /* 尻角度指示 */
  overflag = mTailAdmin -> postTailDegree ( ActionIndex[InputNumber].TailAngle );

  return overflag;

/* ------------------------------------------------------------------- 処理終了 */

)




}
