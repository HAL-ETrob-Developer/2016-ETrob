/* include file */
#include "hal_ev3_std.h"
#include "PatternSequencer_ohs.h"

/**
* コンストラクタ
*/
PatternSequencer_ohs::PatternSequencer_ohs( RunningAdmin_ohs* running_admin, TailAdmin_ohs* tail_admin )
:mRunningAdmin( running_admin ),
 mTailAdmin( tail_admin ) {

	/* 現本体状態構造体初期化 */
	memset( mPatternIndex, 0, sizeof( PATTERN_INDEX ));

	mNowId = INIT_PAT_ID;

	/* 初期値のセット */
	mPatternIndex[INIT_PAT_ID].speed    = INIT__SPEED;
	mPatternIndex[INIT_PAT_ID].ev3_deg  = INIT_EV_DEG;
	mPatternIndex[INIT_PAT_ID].Tail_deg = INIT_TL_DEG;
	mPatternIndex[INIT_PAT_ID].balance  = INIT_BALANC;
}

/**
* デストラクタ
*/
PatternSequencer_ohs::~PatternSequencer_ohs() {
}

/**
* 定量走行指揮
*/
BOOL PatternSequencer_ohs::callPatternRunning( UCHR uc_index )
{
	SCHR cSpeed   = 0;
	SCHR cDegre   = 0;
	SCHR cTailD   = 0;
	BOOL BalanceF = false;

	/* 引数チェック */
	if( uc_index >= PATTERN_NUM ) { return false; }//異常終了

	mNowId = uc_index;

	/* 外部メソッドへ渡す引数の準備 */
	cSpeed = mPatternIndex[mNowId].speed;
	cDegre = mPatternIndex[mNowId].ev3_deg;
	cTailD = mPatternIndex[mNowId].Tail_deg;
	if( mPatternIndex[mNowId].balance == TRUE ) { BalanceF = true; }

	/* 走行指示 */
	if( cSpeed > 50 ) {
		mRunningAdmin->postRunning( cSpeed, cDegre, BalanceF, true );
	} else {
		mRunningAdmin->postRunning( cSpeed, cDegre, BalanceF, false );
	}

	/* 尻角度指示 */
	mTailAdmin->postTailDegree( cTailD );

	return true;//正常終了
}

void PatternSequencer_ohs::callSequencStop()
{
	/* 走行指示：しっぽはそのまま */
	mRunningAdmin->postRunning ( 0, 0, false, false );
	/* 尻角度指示 */
	mTailAdmin->postTailDegree( mPatternIndex[mNowId].Tail_deg );
}


/**
* パターンインデックスの登録
*/
BOOL PatternSequencer_ohs::setPatternIndex( PATTERN_INDEX* p_pattern_index )
{
	if( p_pattern_index == NULL ) { return false; }
	//インデックスの取り込み
	memcpy( mPatternIndex, p_pattern_index, sizeof( mPatternIndex ));
	return true;
}

//現行インデックスNoの取得
UCHR PatternSequencer_ohs::getID() { return mNowId; }

