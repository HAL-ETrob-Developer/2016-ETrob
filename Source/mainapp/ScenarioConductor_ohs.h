/* by ohs50465 T.Ueno */

#ifndef MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_

class ContestScenarioConductor_ohs {
public:
    //生成
    ContestScenarioConductor_ohs();
    //デストラクタ 死ぬときあるよ
        virtual ~ContestScenarioConductor_ohs();

    void execScenario();        //シナリオ実行
    void quitCommand();         //指揮終了
    void setScenario();         //シナリオセット
    void setScenarioUpDate();   //シナリオ更新

private:

};

#endif  // MAINAPP_CONTESTSCENARIOCONDUCTOR_OHS_H_
