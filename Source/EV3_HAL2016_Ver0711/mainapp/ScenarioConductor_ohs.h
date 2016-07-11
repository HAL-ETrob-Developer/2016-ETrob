/* by ohs50465 T.Ueno */

#ifndef MAINAPP_SCENARIOCONDUCTOR_OHS_H_
#define MAINAPP_SCENARIOCONDUCTOR_OHS_H_

class ScenarioConductor_ohs {
public:
    //生成
    ScenarioConductor_ohs();
    //デストラクタ 死ぬときあるよ
        virtual ~ScenarioConductor_ohs();

    void execScenario();
    void quitCommand();
    void setScenario();
    void setScenarioUpDate();

private:

};

#endif  // MAINAPP_SCENARIOCONDUCTOR_OHS_H_
