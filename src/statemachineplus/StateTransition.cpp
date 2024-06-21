//
// Created by giacomo on 21/06/24.
//

#include "debugstatemachine/StateTransition.h"

namespace statemachineplus{
    bool StateTransition::CanTransition(EventSystem& es) const
    {
        auto event = es.HasHappened(trigger);
        if (trigger.empty() || event) return transitionFunction(event);
        return false;
    }
}