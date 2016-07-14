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

/* 動作設定＠デバッグ */
#define PRINT									/* プリント動作 ON/OFF		 */

#define CHECK_STAY								/* 実行終了後停止			 */

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
typedef          bool   BOOL;					/* bool					 */

typedef          long long   SLLG;				/* long	long				 */
typedef unsigned long long   ULLG;				/* unsigned long long		 */

/* ------------------------------------------------------------------------- */
/* 列挙体定義																 */
/* ------------------------------------------------------------------------- */

/* ジャイロ状態 ------------------------------------------------------------ */
enum GYRO_STATE {
	GSTA_UNSTABLE,								/* 不安定					 */
	GSTA_STABILITY,								/* 安定						 */
	GSTA_FALLING								/* 転倒						 */
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
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */

