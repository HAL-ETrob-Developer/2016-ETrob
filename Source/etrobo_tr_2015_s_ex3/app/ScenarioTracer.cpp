/******************************************************************************
 *  ScenarioTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class ScenarioTracer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "ScenarioTracer.h"

/**
 * コンストラクタ
 * @param balancingWalker 倒立走行
 * @param scenario        シナリオ
 * @param timer           タイマ
 */
ScenarioTracer::ScenarioTracer(BalancingWalker* balancingWalker,
                               Scenario* scenario,
                               SimpleTimer* timer)
    : mBalancingWalker(balancingWalker),
      mScenario(scenario),
      mSimpleTimer(timer),
      mState(UNDEFINED) {
}

/**
 * デストラクタ
 */
ScenarioTracer::~ScenarioTracer() {
}

/**
 * シナリオトレースする
 */
void ScenarioTracer::run() {
    switch (mState) {
    case UNDEFINED:
        execUndefined();
        break;
    case INITIAL:
        execInitial();
        break;
    case WALKING:
        execWalking();
        break;
    default:
        break;
    }
}

/**
 * シナリオトレース初期化処理
 */
void ScenarioTracer::initAction() {
    mBalancingWalker->init();
}

/**
 * トレースコマンド設定
 * @param command 走行向き
 */
void ScenarioTracer::setCommand(int command) {
    mBalancingWalker->setCommand(BalancingWalker::LOW, command);
}

/**
 * シーン変更処理
 */
void ScenarioTracer::sceneChangeAction() {
    mScenario->next();

    int command = mScenario->currentSceneCommand();
    setCommand(command);

    mSimpleTimer->setTime(mScenario->currentSceneTime());
    mSimpleTimer->start();
}

/**
 * 未定義状態の処理
 */
void ScenarioTracer::execUndefined() {
    mState = INITIAL;
}

/**
 * 初期状態の処理
 */
void ScenarioTracer::execInitial() {
    initAction();

    mState = WALKING;
}

/**
 * 走行中状態の処理
 */
void ScenarioTracer::execWalking() {
    mBalancingWalker->run();

    if (mSimpleTimer->isTimedOut()) {
        mSimpleTimer->stop();

        sceneChangeAction();
    }
}
