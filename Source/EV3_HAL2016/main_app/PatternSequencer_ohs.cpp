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
SCHR PatternSequencer_ohs::callPatternRunning( UCHR InputNumber, BOOL Balancer ) {

  /* 走行指示 */
  mRunningAdmin -> postRunning ( ActionIndex.RunningSpeed, ActionIndex.RunningAngle, ActionIndex.Balance );

  /* 尻角度指示 */
  mTailAdmin -> postTailDegree ( ActionINdex.TailAngle );

}
