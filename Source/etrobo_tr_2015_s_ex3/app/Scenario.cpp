/******************************************************************************
 *  Scenario.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class Scenario
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Scenario.h"

/**
 * コンストラクタ
 * @param scene 先頭シーン
 */
Scenario::Scenario(Scene* scene)
    : mTopScene(scene),
      mCurrentScene(scene) {
}

/**
 * デストラクタ
 */
Scenario::~Scenario() {
}

/**
 * シーン追加
 * @param scene 追加シーン
 */
void Scenario::add(Scene* scene) {
    if (mTopScene == 0) {
        mTopScene     = scene;
        mCurrentScene = scene;
    } else {
        Scene* s = mTopScene;
        while (s->next != 0) {
            s = s->next;
        }
        s->next = scene;
    }
    scene->next = 0;
}

/**
 * 先頭シーン取得
 * @return 先頭シーン
 */
Scene* Scenario::top() const {
    return mTopScene;
}

/**
 * 現在シーン取得
 * @return 現在シーン
 */
Scene* Scenario::current() const {
    return mCurrentScene;
}

/**
 * 次のシーンへ進める
 * @return 実行シーン
 */
Scene* Scenario::next() {
    if (mCurrentScene != 0) {
        mCurrentScene = (mCurrentScene->next == 0) ?
            mTopScene :
            mCurrentScene->next;
    }
    return mCurrentScene;
}

/**
 * 現在シーンコマンド取得
 * @return コマンド
 */
int Scenario::currentSceneCommand() const {
    return (mCurrentScene == 0) ? 0 : mCurrentScene->command;
}

/**
 * 現在シーン実行時間取得
 * @return 実行時間
 */
uint32_t Scenario::currentSceneTime() const {
    return (mCurrentScene == 0) ? 0 : mCurrentScene->time;
}
