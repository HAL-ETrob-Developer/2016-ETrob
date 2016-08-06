/* by ohs50465 T.UENO */

#ifndef MAINAPP_PATTERNSEQUENCER_OHS_H_
#define MAINAPP_PATTERNSEQUENCER_OHS_H_
#include "hal_ev3_std.h"

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
    //デストラクタ 死ぬときあるよ
        virtual ~PatternSequencer_ohs();

    void callPatternRunning();

private:

};

#endif  // MAINAPP_PATTERNSEQUENCER_OHS_H_
