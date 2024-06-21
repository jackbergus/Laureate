//
// Created by giacomo on 21/06/24.
//

#include "debugstatemachine/StateMachinePlus.h"

namespace statemachineplus {

    void StateMachinePlus::Update(float dt)
    {
        for (const auto& i : ComponentContainer)
        {
            auto subStateMachine = i.second;
            if (subStateMachine)
                subStateMachine->Update(dt);
        }
    }

    std::string StateMachinePlus::Print(int index)
    {
        std::string buffer("[StateMachinePlus]\n");
        for (auto& i : ComponentContainer)
        {
            for (int j = 0; j < index; ++j) {
                buffer += "    ";
            }
            buffer += "(" + i.first + ")" + i.second->Print(index + 1);
        }
        return buffer;
    }

    void StateMachinePlus::GetActiveComponentArr(std::vector<std::string>& arr)
    {
        for (auto& it : ComponentContainer)
        {
            it.second->GetActiveComponentArr(arr);
        }
    }
} // debugstatemachine