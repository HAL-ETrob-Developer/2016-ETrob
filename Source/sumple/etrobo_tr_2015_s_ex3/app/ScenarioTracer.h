/******************************************************************************
 *  ScenarioTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class ScenarioTracer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_SCENARIOTRACER_H_
#define EV3_APP_SCENARIOTRACER_H_

#include "BalancingWalker.h"
#include "SimpleTimer.h"
#include "Scenario.h"

class ScenarioTracer {
public:
    ScenarioTracer(BalancingWalker* balancingWalker,
                   Scenario* scenario,
                   SimpleTimer* timer);
    virtual ~ScenarioTracer();

    void run();

private:
    enum State {
        UNDEFINED,
        INITIAL,
        WALKING
    };

    BalancingWalker* mBalancingWalker;
    Scenario* mScenario;
    SimpleTimer* mSimpleTimer;
    State mState;

    void initAction();
    void setCommand(int command);
    void sceneChangeAction();
    void execUndefined();
    void execInitial();
    void execWalking();
};

#endif  // EV3_APP_SCENARIOTRACER_H_
