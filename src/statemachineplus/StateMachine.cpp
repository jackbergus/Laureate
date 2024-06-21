//
// Created by junlin luo
//

#include "debugstatemachine/StateMachine.h"
#include <debugstatemachine/StateTransition.h>

namespace statemachineplus{
void
StateMachine::Update(float dt) {
    if (activeComponent == nullptr)return;
    activeComponent->Update(dt);
    //getInstance the transition set starting from this state node;
    auto range = get_transitions(activeComponent);

    for (auto& i = range.first; i != range.second; ++i)
    {
        if (!i->second->enable)continue;
        if (i->second->CanTransition(*es))
        {
            activeComponent = i->second->GetDestinationState();
        }
    }
}
std::string StateMachine::Print(int index)
{
    std::string active;
    for (auto& it : ComponentContainer)
    {
        if (it.second == activeComponent)
        {
            active = it.first;
            break;
        }
    }
    std::string buffer("[StateMachine]");
    buffer += "<" + active + ">\n";
    for (auto i : ComponentContainer)
    {
        for (int j = 0; j < index; ++j) {
            buffer += "    ";
        }
        buffer += "(" + i.first + ")" + i.second->Print(index + 1);
    }
    return buffer;
}
void StateMachine::AddTransition(std::shared_ptr<StateTransition> t) {
    allTransitions.emplace(t->GetSourceState(), t);
}

void StateMachine::GetActiveComponentArr(std::vector<std::string>& arr)
{
    for (auto& it : ComponentContainer)
    {
        if (it.second == activeComponent)
        {
            arr.emplace_back(it.first);
        }
        it.second->GetActiveComponentArr(arr);
    }
}

std::pair<TransitionIterator, TransitionIterator> StateMachine::get_transitions(std::shared_ptr<AbstractComponent> state)
{
    return allTransitions.equal_range(state);
}
}