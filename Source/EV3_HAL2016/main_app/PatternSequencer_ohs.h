/* by ohs50465 T.UENO */

#ifndef MAINAPP_PATTERNSEQUENCER_OHS_H_
#define MAINAPP_PATTERNSEQUENCER_OHS_H_

/* include file */
#include "hal_ev3_std.h"

/* 構造体 実行動作インデックス */
typedef struct {
  int32_t RunningSpeed;
  int32_t RunningAngle;
  int32_t TailAngle;
  BOOL    Balance;
}RUNNING_PAT_INDEX;

class PatternSequencer_ohs {
public:
    //生成
    PatternSequencer_ohs();
    //デストラクタ
        virtual ~PatternSequencer_ohs();

    SCHR callPatternRunning( UCHR InputNumber, BOOL Balancer );

private:
  RUNNING_PAT_INDEX ActionIndex;
  RunningAdmin_ohs*      mRunningAdmin;
  TailAdmin_ohs*         mTailAdmin;
};

#endif  // MAINAPP_PATTERNSEQUENCER_OHS_H_
