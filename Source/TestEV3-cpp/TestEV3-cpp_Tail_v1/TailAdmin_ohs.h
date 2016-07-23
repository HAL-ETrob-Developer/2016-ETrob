/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_TAILADMIN_OHS_H_
#define DEVICEOPE_TAILADMIN_OHS_H_

#define P_GAIN		( 2.5F)
#define D_GAIN		( 5.0F)
#define MAX_TARGET	(  100)
#define MIN_TARGET	( -100)

class TailAdmin_ohs
{
    public:
    //生成
    TailAdmin_ohs( ev3api::Motor& tail_wheel );
    //デストラクタ 死ぬときあるよ
    ~TailAdmin_ohs();

    void callTailDegreeUpdate();
	BOOL postTailDegree( int32_t postTailDeg );
    void callTailDegree();
    int32_t getTailDegree();


	private:
    ev3api::Motor& mTailWheel;
    int32_t mTailDeg;
    SINT mTailTarget;
    SINT mOldTarget;
};

#endif  // DEVICEOPE_TAILADMIN_OHS_H_
