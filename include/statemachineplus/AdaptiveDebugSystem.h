/*
 * AdaptiveDebugSystem.h
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

#ifndef LANGUAGE_ADAPTIVEDEBUGSYSTEM_H
#define LANGUAGE_ADAPTIVEDEBUGSYSTEM_H

#include <ostream>
#include <stack>
#include <vector>
#include <memory>
#include <debugstatemachine/StateMachine.h>

/*
 * Adaptive system
*
* Introduces two concepts: environment and agent
*
* Environment: The context in which the agent runs. Here, it specifically refers to the environment composed of monsters, debug state machines, and dragons
*
* Agent: The individual that needs to be observed. Here, it refers to the state machine of monsters and dragons (the player does not need to be paid attention to in this environment for the time being)
 */
namespace statemachineplus {
    class State;
    class StateMachine;
    class EventSystem;
    using Path = std::stack<std::shared_ptr<State>>;
    using Environment = std::pair<std::string,std::vector<StateMachine*>>;
    using EnvContainer = std::vector<std::shared_ptr<Environment>>;
    class AdaptiveDebugSystem
    {
        friend std::ostream& operator<<(std::ostream& os, const AdaptiveDebugSystem& obj)
        {
            std::string buffer("AdaptiveDebugSystem:\n");
            for(const auto i: obj.env_container_)
            {
                buffer += i->first+":\n";
                for(const auto j:i->second)
                {
                    buffer += j->Print(0)+"\n";
                }
            }
            return os << buffer;
        }

    public:
//        static AdaptiveDebugSystem* getInstance()
//        {
//            if(instance==nullptr)
//            {
//                instance = new AdaptiveDebugSystem();
//            }
//            return instance;
//        }
        void insert(std::shared_ptr<Environment>& env);
        void update(float dt);
    protected:
        EnvContainer env_container_;
    private:
        std::shared_ptr<EventSystem> es;
//        static AdaptiveDebugSystem* instance;
        AdaptiveDebugSystem(std::shared_ptr<EventSystem> es);
        void adjust(Path path, StateMachine* state_machine);
        std::shared_ptr<Environment> find_deadlock_env();
        Path re_plan(StateMachine* state_machine);
    };
}

#endif //LANGUAGE_ADAPTIVEDEBUGSYSTEM_H
