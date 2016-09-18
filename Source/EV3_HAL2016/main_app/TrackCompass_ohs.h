#ifndef MAINAPP_TRACKCOMPASS_OHS_H_
#define MAINAPP_TRACKCOMPASS_OHS_H_

/* include file */
#include "../device_ope/RunningAdmin_ohs.h"
#include "../calculation/RunLineCalculator_ohs.h"

#define RAT_TRN_MAX		( 		  1500 )
#define SND_TRN_MAX		( 			50 )
#define RA_PK     		( 		  0.5F )

#define TC_TOLERANCE	( 		    10 )

#define RA_STD_SPD		( 			 0 )
#define RA_ALT_SPD		( 			20 )
#define RA_ALT_RSPD		( 		   -20 )
#define RA_ALT_RT_SPD	( 		   -10 )
#define RA_STD_BRN		( 		  true )
#define RA_STD_BRK		( 		  true )

#define RA_NOW_GAIN  (     0.1F )
#define RA_OLD_GAIN  (     0.9F )


class TrackCompass_ohs {
public:
	//生成
	TrackCompass_ohs( RunningAdmin_ohs* running_admin, RunLineCalculator_ohs* running_line_calculator );
	//デストラクタ
	~TrackCompass_ohs();

	/* メソッド */
	void callReferenceSearch();
	void setReferenceAxis();
	BOOL callRAxisTurn( int32_t target );
	BOOL callRAxisMove( int32_t move_length, BOOL balancer );
	BOOL getRAxisTurnFinish( int32_t target );


private:

	/* メソッド */
    int32_t getReferenceAxis();
    int8_t calcFollowDegree( int32_t target );

	/* メンバ */
	RunningAdmin_ohs* mRunningAdmin;
    RunLineCalculator_ohs* mRunLineCalculator;

    FLOT    mReferenceAxis;
	int32_t mNowRAxis;
	int32_t mTargetDirection;
	BOOL    mRAxisTurnFinish;
};

#endif  // MAINAPP_TRACKCOMPASS_OHS_H_
