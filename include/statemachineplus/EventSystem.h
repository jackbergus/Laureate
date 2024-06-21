/*
 * EventSystem.h
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

#ifndef LANGUAGE_EVENTSYSTEM_H
#define LANGUAGE_EVENTSYSTEM_H

#include <list>
#include <functional>
#include "AbstractStateMachine.h"
#include <initializer_list>
#include <memory>

namespace statemachineplus {

    struct EVENT;
    struct EVENT_DEFINE {
        std::string name;
        bool delay = false;
        std::list<std::function<void(EVENT*)>> listFunc; // TODO: scriptable via script

        EVENT_DEFINE() = default;
        EVENT_DEFINE(const EVENT_DEFINE&) = default;
        EVENT_DEFINE(EVENT_DEFINE&&) = default;
        EVENT_DEFINE& operator=(const EVENT_DEFINE&) = default;
        EVENT_DEFINE& operator=(EVENT_DEFINE&&) = default;
    };
    struct EVENT {
        EVENT_DEFINE* pEventDef;
        std::vector<std::string> vArg;
        bool operator == (const EVENT& other)
        {
            if (other.pEventDef != pEventDef) return false;
            if (other.vArg.size() != vArg.size()) return false;
            for (size_t i = 0; i < vArg.size(); i++)
            {
                if (vArg[i] != other.vArg[i]) return false;
            }
            return true;
        }
    };

    using EventDefContainer = std::map<std::string, EVENT_DEFINE>;
    using EventDefContainerIterator = EventDefContainer::iterator;
    using EventQueueIterator = std::list<std::shared_ptr<EVENT>>::iterator;
    class EventSystem :public AbstractStateMachine
    {
    public:
        std::vector<EVENT_DEFINE> eventsLocalCopy;
        void Update(float dt) override;
        std::string Print(int index) override;
        void GetActiveComponentArr(std::vector<std::string>& arr) override{}
        void RegisterEventHandler(const std::string&, const std::function<void(EVENT*)>&);
        void PushEvent(const std::string&, std::initializer_list<std::string> list);
        EventSystem(std::vector<EVENT_DEFINE>& g_Events);
        void init();
//        static EventSystem* getInstance() {
//            if(instance==nullptr)
//            {
//                instance = new EventSystem();
//            }
//            return instance;
//        }
        std::shared_ptr<EVENT> HasHappened(const std::string&);
        void Reset();
    private:
        static EventSystem* instance;

        void processEvent(EVENT& event);
        EventDefContainer eventDefContainer;
        std::list<std::shared_ptr<EVENT>> eventQueue;
        std::list<std::shared_ptr<EVENT>> eventQueueDelay;
        std::vector<std::shared_ptr<EVENT>> eventRecords;
        float time = 0.0f;
    };

} // debugstatemachine

#endif //LANGUAGE_EVENTSYSTEM_H
