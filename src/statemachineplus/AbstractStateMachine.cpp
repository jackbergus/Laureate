//
// Created by junlin luo
//

#include "debugstatemachine/AbstractStateMachine.h"
#include <debugstatemachine/State.h>

namespace statemachineplus {

    void AbstractStateMachine::AddComponent(const std::string& name, std::shared_ptr<AbstractComponent> compoent)
    {
        ComponentContainer.insert(std::make_pair(name, std::move(compoent)));
    }

   std::shared_ptr<AbstractComponent> AbstractStateMachine::GetComponent(const std::string& name)
    {
        auto temp = ComponentContainer.find(name);
        if (temp != ComponentContainer.end())return temp->second;
        for (const auto& i : ComponentContainer) {

            if ((std::dynamic_pointer_cast<State>(i.second) == nullptr) && (std::dynamic_pointer_cast<AbstractStateMachine>(i.second) !=
                    nullptr)) {
                auto sub = std::dynamic_pointer_cast<AbstractStateMachine>(i.second);
                auto result = sub->GetComponent(name);
                if (result != nullptr)
                    return result;
            }
        }
        return nullptr;
    }
} // debugstatemachine