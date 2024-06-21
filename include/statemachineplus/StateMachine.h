/*
 * StateMachine.h
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

#ifndef LANGUAGE_STATEMACHINE_H
#define LANGUAGE_STATEMACHINE_H

#include "AbstractStateMachine.h"


namespace statemachineplus {
    class StateTransition;
    class EventSystem;
    using TransitionContainer = std::multimap<std::shared_ptr<AbstractComponent>, std::shared_ptr<StateTransition>>;
    using TransitionIterator = TransitionContainer::iterator;
    class StateMachine : public AbstractStateMachine {
    public:
        EventSystem* es;
        StateMachine(const std::string& name, std::shared_ptr<AbstractComponent> defaultComponent,AbstractComponent* exp=nullptr,EventSystem* es= nullptr)
                :activeComponent(defaultComponent), expComponent(exp), es{es}{
            AddComponent(name, defaultComponent);
        }
        ~StateMachine() override {  }
        void Update(float dt) override;
        std::string Print(int index) override;
        void AddTransition(std::shared_ptr<StateTransition> t);
        void GetActiveComponentArr(std::vector<std::string>& arr) override;
        void SetActiveComponent(std::shared_ptr<AbstractComponent> active)
        {
            activeComponent = std::move(active);
        }
        TransitionContainer get_all_transitions() const
        {
            return allTransitions;
        }

        std::shared_ptr<AbstractComponent> get_active_component() const
        {
            return activeComponent;
        }

        std::shared_ptr<AbstractComponent> get_exp_component() const
        {
            return expComponent;
        }
        std::pair<TransitionIterator, TransitionIterator> get_transitions(std::shared_ptr<AbstractComponent> state);
    protected:
        std::shared_ptr<AbstractComponent> activeComponent;
        std::shared_ptr<AbstractComponent> expComponent;
        TransitionContainer allTransitions;
    };
}

#endif //LANGUAGE_STATEMACHINE_H
