/* by ohs50465 T.UENO */
#ifndef CALCLATION_RUNNINGLINECALCULATOR_OHS_H_
#define CALCLATION_RUNNINGLINECALCULATOR_OHS_H_

/* define file */

class RunningLineCalculator_ohs {
public:
    //生成
    RunningLineCalculator_ohs();
    //デストラクタ
    ~RunningLineCalculator_ohs();

    void calcRunningLine();

private:
	/* メンバ */
	int8_t mColorState;
	int8_t mLastColor;
};

#endif  // RUNNINGLINECALCULATOR_OHS_H_
