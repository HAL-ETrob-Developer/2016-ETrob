/* by ohs50465 T.UENO */

#ifndef DEVICEOPE_TAILADMIN_OHS_H_
#define DEVICEOPE_TAILADMIN_OHS_H_

class TailAdmin_ohs {
public:
    //生成
    TailAdmin_ohs();
    //デストラクタ 死ぬときあるよ
        virtual ~TailAdmin_ohs();

    void callTailDegreeUpDate();
    void postTailDegree();
    void callTailDegree();
    void getTailDegree();


private:

};

#endif  // DEVICEOPE_TAILADMIN_OHS_H_
