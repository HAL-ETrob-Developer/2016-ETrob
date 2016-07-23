/*
 *      サンプルプログラム(1)のヘッダファイル
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ターゲット依存の定義
 */
#include "target_test.h"

/*
 *  各タスクの優先度の定義
 */

#define MAIN_PRIORITY           ( TMIN_APP_TPRI )             // メインタスクの優先度
#define INTERRUPT_PRIORITY      ( MAIN_PRIORITY + 1 )         // 割り込みタスクの優先度

//#define TRACER_PRIORITY         ( INTERRUPT_PRIORITY + 1 )    // 基本動作タスクの優先度
//#define BT_PRIORITY             ( TRACER_PRIORITY + 1 )       // Bluetoothタスクの優先度

#define TRACER_PRIORITY         ( INTERRUPT_PRIORITY + 2 )    // 基本動作タスクの優先度
#define BT_PRIORITY             ( INTERRUPT_PRIORITY + 1 )       // Bluetoothタスクの優先度


/*
 *  ターゲットに依存する可能性のある定数の定義
 */

#ifndef TASK_PORTID
#define TASK_PORTID     1           /* 文字入力するシリアルポートID */
#endif /* TASK_PORTID */

#ifndef STACK_SIZE
#define STACK_SIZE      4096        /* タスクのスタックサイズ */
#endif /* STACK_SIZE */

/*
 *  関数のプロトタイプ宣言
 */
#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void bt_task(intptr_t exinf);
extern void tracer_task(intptr_t exinf);
extern void ev3_cyc_tracer(intptr_t exinf);
extern void interrupt_task(intptr_t exinf);

static void user_system_create( void );
static void user_system_destroy( void );

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
