/*
 * StateTransition.h
 * This file is part of StateMachinePlus
 *
 * Copyright (C) 2022 - Junlin Luo
 *
 * StateMachinePlus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * StateMachinePlus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with StateMachinePlus. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by junlin luo
//

#ifndef LANGUAGE_STATETRANSITION_H
#define LANGUAGE_STATETRANSITION_H

#include "AbstractComponent.h"
#include "EventSystem.h"

namespace statemachineplus {
    class State;
    using StateTransitionFunction = std::function<bool(std::shared_ptr<EVENT>&)>;
    class StateTransition {
    public:
        StateTransition(std::shared_ptr<AbstractComponent> source, std::shared_ptr<AbstractComponent> dest, StateTransitionFunction f, std::string _trigger,
                        bool _enable=true) {
            sourceState = source;
            destinationState = dest;
            transitionFunction = std::move(f);
            trigger = _trigger;
            enable = _enable;
        }
        bool CanTransition(EventSystem& es) const;
        inline std::shared_ptr<AbstractComponent> GetDestinationState() const { return destinationState; }
        inline std::shared_ptr<AbstractComponent> GetSourceState() const { return sourceState; }
        bool enable;
    protected:
        std::shared_ptr<AbstractComponent> sourceState;
        std::shared_ptr<AbstractComponent> destinationState;
        StateTransitionFunction transitionFunction;
        std::string trigger;
    };
}




#endif //LANGUAGE_STATETRANSITION_H
