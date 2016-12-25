/* ------------------------------------------------------------------------- */
/* hal_ev3_std.h															 */
/* EV3_HAL_OSAKA  標準的な定数群											 */
/* 標準的な定数のヘッダファイル												 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* 	番号	更新内容								更新日		名前		 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								2016/07/12	大塚  信晶	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル															 */
/* ------------------------------------------------------------------------- */

#include <stdio.h>								/* 標準入出力ヘッダ			 */

/* ------------------------------------------------------------------------- */
/* 定数定義																	 */
/* ------------------------------------------------------------------------- */

/* 関数 戻り値用 */
#define FUNC_OK				( 		   1 )		/* 正常終了					 */
#define FUNC_NG				(		  -1 )		/* 異常終了					 */
#define FUNC_ARG_NG			(		  -2 )		/* 引数の設定エラー			 */

/* フラグ管理 */
#define FLG_ON				( 		   1 )		/* フラグのON				 */
#define FLG_OFF				( 		   0 )		/* フラグのOFF				 */

/* bool */
#define TRUE				( 		   1 )		/* 真						 */
#define FALSE				( 		   0 )		/* 偽						 */

/* プリント操作 */
#define STR_MODE			(		   1 )		/* 文字列print_mode 		 */
#define CHR_MODE			(		   2 )		/* 文字  print_mode 		 */
#define DSI_MODE			(		   3 )		/* SINT  print_mode 		 */
#define DUC_MODE			(		   4 )		/* UCHR  print_mode 		 */
#define DSC_MODE			(		   5 )		/* USHR  print_mode 		 */

/* 構造体要素数 */
#define _PATTERN_NUM 		 (		 40 )/* パターンインデックスサイズ */
#define _SCENARIO_MAX_NUM_R  (  	 50 )/* シナリオインデックスサイズ */
#define _SCENARIO_MAX_NUM_L  (  	 50 )/* シナリオインデックスサイズ */
#define _SCENARIO_MAX_NUM	 (  	100 )/* シナリオインデックスサイズ */

//達成条件:enum化するとEV3RT_2016_FORMと連携取り辛いので
#define _CLS_BLK    (     0 )
#define _CLS_GRY    (     1 )
#define _CLS_WHT    (     2 )
#define _RUN_MLG    (     3 )
#define _EV3_DEG    (     4 )
#define _TIL_DEG    (     5 )
#define _GYR__ST    (     6 )
#define _GYR_UST    (     7 )
#define _EX_SLIP    (     8 )
#define _EX_END     (     9 )
#define _CLS_LIN    (    10 )
#define _EX_JUMP    (    11 )
#define _RAXIS_T    (    12 )
#define _EVENT_NUM  (    13 )



/* 動作設定＠デバッグ */
#define PRINT									/* プリント動作 ON/OFF		 */
// #define INTERRUPT_CHK							/* メトロノーム ON/OFF		 */
#define CHECK_STAY								/* 実行終了後停止			 */
// #define SOUND_ANSWER							/* アンサー音 ON/OFF		 */
// #define TRANSITION_SOUND						/* 状態遷移チェック音 ON/OFF		 */
// #define FALLING_STOP							/* 本体の転倒を検知すると停止する */

/* ------------------------------------------------------------------------- */
/* typedef宣言																 */
/* ------------------------------------------------------------------------- */
typedef          char   SCHR;					/* char						 */
typedef unsigned char   UCHR;					/* unsigned char			 */
typedef          short  SSHT;					/* short					 */
typedef unsigned short  USHT;					/* unsigned short			 */
typedef          long   SLNG;					/* long						 */
typedef unsigned long   ULNG;					/* unsigned long			 */
typedef          int    SINT;					/* int						 */
typedef unsigned int    UINT;					/* unsigned int				 */
typedef          float  FLOT;					/* float					 */
typedef          double DBLE;					/* double					 */
typedef          bool   BOOL;					/* bool						 */

typedef          long long   SLLG;				/* long	long				 */
typedef unsigned long long   ULLG;				/* unsigned long long		 */

/* ------------------------------------------------------------------------- */
/* 列挙体定義																 */
/* ------------------------------------------------------------------------- */

/* ジャイロ状態 ------------------------------------------------------------ */
enum GYRO_STATE {
	GSTA_UNDECIDED,								/* 不定状態					 */
	GSTA_UNSTABLE,								/* 不安定					 */
	GSTA_STABILITY,								/* 安定					 */
	GSTA_FALLING								/* 転倒					 */
};

/* カラーセンサカラー ------------------------------------------------------ */
enum SENC_CLR {
	SCLR_BLACK,									/* ブラック					 */
	SCLR_GRAY,									/* グレー					 */
	SCLR_WHITE									/* ホワイト					 */
};
/* 選択走行ルート ---------------------------------------------------------- */
enum RUNNING_ROUTE {
	RROUTE_WAITING,								/* 不安定					 */
	RROUTE_RIGHT,								/* 右コース					 */
	RROUTE_LEFT									/* 左コース					 */
};
/* トレースモード ---------------------------------------------------------- */
enum TRACE_MODE {
	TMODE_EDGE,									/* エッジトレース			 */
	TMODE_SEARCH								/* 探索						 */
};

/* ------------------------------------------------------------------------- */
/* 構造体定義																 */
/* ------------------------------------------------------------------------- */

/* 構造体 PID制御設定ファイル */
typedef struct _PID_SETTING{
	float fTerSpeed;   /* 目標速度 */
	float fTerRefLv;   /* 目標光学値 */
	float fSpdP;       /* 前進Pゲイン */
	float fSpdI;       /* 前進Iゲイン */
	float fSpdD;       /* 前進Dゲイン */
	float fDegP;       /* 旋回Pゲイン */
	float fDegI;       /* 旋回Iゲイン */
	float fDegD;       /* 旋回Dゲイン */
}PID_SETTING;

/* 構造体 シナリオ */
typedef struct _SCENARIO_INDEX {
    UCHR move_event;   /* 達成条件 */
    UCHR pattern_id;   /* 実行動作番号 */
    UCHR next_scene;   /* 次の遷移番号 */
    UCHR dummy;        /* バウンダリ対策 */
    SLNG event_value;  /* 達成条件に付随する値 */
}SCENE_INDEX;

/* 構造体 実行動作インデックス */
typedef struct _PATTERN_INDEX{
	SCHR speed;        /* 前進速度 */
	SCHR ev3_deg;      /* 旋回角度 */
	SCHR Tail_deg;     /* 尻尾角度 */
	UCHR balance;      /* バランス走行の有無 */
}PATTERN_INDEX;

/* 構造体 全設定ファイル統合 */
typedef struct _EV3_SETTING{
	PID_SETTING   nmPidSetting;/* 構造体 PID制御設定ファイル＠通常 */
	PID_SETTING   scPidSetting;/* 構造体 PID制御設定ファイル＠第二設定 */
	SCENE_INDEX   sceneIndexS[_SCENARIO_MAX_NUM];/* 構造体 シナリオ */
	PATTERN_INDEX patrnIndexS[_PATTERN_NUM];/* 構造体 実行動作インデックス */
}EV3_SETTING;

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */

