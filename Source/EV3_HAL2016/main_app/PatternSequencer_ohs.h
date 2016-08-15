/* by ohs50465 T.UENO */

#ifndef MAINAPP_PATTERNSEQUENCER_OHS_H_
#define MAINAPP_PATTERNSEQUENCER_OHS_H_

/* include file */
#include "../device_ope/RunningAdmin_ohs.h"
#include "../device_ope/TailAdmin_ohs.h"

#define INIT__SPEED (		 0 )/* 初期パターン：速度 */
#define INIT_EV_DEG (		 0 )/* 初期パターン：本体角度 */
#define INIT_TL_DEG (		 0 )/* 初期パターン：尾角度 */
#define INIT_BALANC (		 0 )/* 初期パターン：バランス有無 */

#define INIT_PAT_ID (		 0 )/* 初期パターンを指し示す */
#define PATTERN_NUM (		20 )/* パターンインデックスサイズ */

/* 構造体 実行動作インデックス */
typedef struct _PATTERN_INDEX{
	SCHR speed;
	SCHR ev3_deg;
	SCHR Tail_dee;
	UCHR balance;
}PATTERN_INDEX;

class PatternSequencer_ohs {
public:
	//生成
	PatternSequencer_ohs( RunningAdmin_ohs* running_admin, TailAdmin_ohs* tail_admin );
	//デストラクタ
	~PatternSequencer_ohs();

	//定量走行指揮
	BOOL callPatternRunning( UCHR uc_index );
	//インデックス外部登録
	BOOL setPatternIndex( PATTERN_INDEX* p_pattern_index );

private:

	RunningAdmin_ohs* mRunningAdmin;
	TailAdmin_ohs*    mTailAdmin;

	PATTERN_INDEX     mPatternIndex[PATTERN_NUM];
};

#endif  // MAINAPP_PATTERNSEQUENCER_OHS_H_
