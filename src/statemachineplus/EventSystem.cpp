//
// Created by giacomo on 21/06/24.
//

#include "debugstatemachine/EventSystem.h"


namespace statemachineplus {
    EventSystem::EventSystem(std::vector<EVENT_DEFINE>& g_Events) : eventsLocalCopy{g_Events} {
        for (int i = 0; i < eventsLocalCopy.size(); i++)
        {
            eventDefContainer[eventsLocalCopy[i].name] = (eventsLocalCopy[i]);
        }
    }

    std::string EventSystem::Print(int index)
    {
        std::string buffer;
        buffer += "Event Records:\n";
        for (const auto& i : eventRecords) {
            buffer += "[" + i->pEventDef->name + "]";
            for (const auto& j : i->vArg)
            {
                buffer += "("+j + ")";
            }
            buffer += "\n";
        }
        return buffer;
    }

    void EventSystem::Update(float dt)
    {
        if (!(eventQueueDelay.empty()))
        {
            const float WORK_STEP = 10;
            time += dt;
            if (time >= WORK_STEP)
            {
//                auto event = *(eventQueueDelay.begin());
                processEvent(**eventQueueDelay.begin());
                eventQueueDelay.erase(eventQueueDelay.begin());
                time = 0.0f;
            }
        }
        EventQueueIterator it;
        for (it = eventQueue.begin(); it != eventQueue.end(); it++)
        {
//            auto& event = *it;
            bool bMultiPushed = false;
            for (auto itPrev = eventQueue.begin(); itPrev != it; itPrev++)
            {
                if (*itPrev == *it)
                {
                    bMultiPushed = true;
                    break;
                }
            }

            if (bMultiPushed) continue;
            processEvent(**it);
        }
        eventQueue.clear();
    }

    void EventSystem::RegisterEventHandler(const std::string& name, const std::function<void(EVENT*)>& func)
    {
        eventDefContainer[name].listFunc.emplace_back(func);
    }

    void EventSystem::PushEvent(const std::string& name, std::initializer_list<std::string> list)
    {
        auto event = std::make_shared<EVENT>();
        event->pEventDef = &eventDefContainer[name];
        event->vArg.insert(event->vArg.end(), list.begin(), list.end());
        if (event->pEventDef->delay)
            eventQueueDelay.emplace_back(event);
        else
            eventQueue.emplace_back(event);
        eventRecords.emplace_back(event);
    }

    std::shared_ptr<EVENT> EventSystem::HasHappened(const std::string& name)
    {
        for (auto& event : eventQueue) {
            if (event->pEventDef->name == name)
                return event;
        }
        for (auto& event : eventQueueDelay) {
            if (event->pEventDef->name == name)
                return event;
        }
        return nullptr;
    }

    void EventSystem::Reset()
    {
        eventQueue.clear();
        eventQueueDelay.clear();
        for(auto& [k,v]:eventDefContainer)
        {
            v.listFunc.clear();
        }
        init();
    }

    void EventSystem::init()
    {

        for (int i = 0; i < eventsLocalCopy.size(); i++)
        {
            eventDefContainer[eventsLocalCopy[i].name] = (eventsLocalCopy[i]);
        }
    }

    void EventSystem::processEvent(EVENT& event)
    {
        EVENT_DEFINE* pEventDef = event.pEventDef;
        if (!pEventDef) return;


        if (!(pEventDef->listFunc.empty()))
        {
            for (auto func = event.pEventDef->listFunc.begin(); func != event.pEventDef->listFunc.end(); func++)
            {
                (*func)(&event);
            }
        }
    }

} // debugstatemachine