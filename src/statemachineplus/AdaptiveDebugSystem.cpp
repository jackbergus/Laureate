//
// Created by giacomo on 21/06/24.
//

#include "debugstatemachine/AdaptiveDebugSystem.h"

#include "debugstatemachine/State.h"
#include "debugstatemachine/StateMachine.h"
#include "debugstatemachine/StateTransition.h"
#include <forward_list>

namespace statemachineplus {
//AdaptiveDebugSystem* AdaptiveDebugSystem::instance=nullptr;
struct Node
{
    Node( std::shared_ptr<State> state) :
            f(0), g(0), h(0), state(std::move(state))
    {}
    int f, g, h;
    std::shared_ptr<State> state;
};
bool cmp(const std::forward_list<std::shared_ptr<Node>> a, const std::forward_list<std::shared_ptr<Node>> b) {
    return a.begin()->get()->f < b.begin()->get()->f;
}

AdaptiveDebugSystem::AdaptiveDebugSystem(std::shared_ptr<EventSystem> es) : es{std::move(es)} {

}

void AdaptiveDebugSystem::insert(std::shared_ptr<Environment>& env)
{
    env_container_.emplace_back(env);
}

void AdaptiveDebugSystem::update(float dt)
{
    const auto env = find_deadlock_env();
    if (env == nullptr)return;
    for(const auto i:env->second)
    {
        const auto path = re_plan(i);
        adjust(path,i);
    }
    es->PushEvent("fix_"+env->first, {});
}

void AdaptiveDebugSystem::adjust(Path path, StateMachine* state_machine)
{
    const auto size = path.size();
    for (size_t i = 0; i < size - 1; ++i)
    {
        const auto currentNode = path.top();
        path.pop();
        const auto destNode = path.top();
        auto currentNodeRange = state_machine->get_transitions(currentNode);
        auto destNodeRange = state_machine->get_transitions(destNode);
        for (auto& j = currentNodeRange.first; j != currentNodeRange.second; ++j)
        {
            if (j->second->GetDestinationState() == destNode)
            {
                j->second->CanTransition(*es);
                break;
            }
        }
        //for (auto& k = destNodeRange.first; k != destNodeRange.second; ++k)
        //{
        //	if (k->second->GetDestinationState() == currentNode)
        //	{
        //		k->second->enable = false;// turn off previous trans
        //		break;
        //	}
        //}
    }
    state_machine->SetActiveComponent(path.top());
}

std::shared_ptr<Environment> AdaptiveDebugSystem::find_deadlock_env()
{
    for (auto& env : env_container_)
    {
        for (const auto& state_machine : env->second)
        {//	TODO: stateMachine plus
            const auto active = state_machine->get_active_component();
            const auto exp = state_machine->get_exp_component();
            if (exp == nullptr)
                continue;
            if (active == exp)
                continue;
            auto range = state_machine->get_transitions(active);
            bool HasOutGoing = false;

            if(active)

                for (auto& i = range.first; i != range.second; ++i)
                {
                    if (i->second->enable&& i->second->GetSourceState()!=i->second->GetDestinationState())
                    {
                        HasOutGoing = true;
                        break;
                    }
                }
            if (!HasOutGoing)
            {
                return env;
            }
        }
    }
    return nullptr;
}

statemachineplus::Path AdaptiveDebugSystem::re_plan(StateMachine* state_machine)
{
    statemachineplus::Path result;
    auto active= std::dynamic_pointer_cast<State>(state_machine->get_active_component());
    auto exp= std::dynamic_pointer_cast<State>(state_machine->get_exp_component());
    std::vector<std::forward_list<std::shared_ptr<Node>>> openList;
    std::vector<std::forward_list<std::shared_ptr<Node>>> closeList;

    auto allState = state_machine->get_component_container();
    auto allTrans = state_machine->get_all_transitions();
    auto node = std::make_shared<Node>(active);
    auto temp = std::forward_list<std::shared_ptr<Node>>();
    temp.push_front(node);
    openList.emplace_back(temp);

    while (!openList.empty())
    {
        std::sort(openList.begin(), openList.end(), cmp);
        auto currentNode = openList[0];
        openList.erase(openList.begin());
        closeList.emplace_back(currentNode);
        std::pair<TransitionIterator, TransitionIterator> range = allTrans.equal_range(currentNode.begin()->get()->state);
        if (currentNode.begin()->get()->state == exp)
        {
            for (auto& i : currentNode)
            {
                result.push(i->state);
            }
            break;
        }
        auto currentG = currentNode.begin()->get()->g;
        for (auto& i = range.first; i != range.second; ++i)
        {

            bool skip = false;
            const auto newState = std::dynamic_pointer_cast<State>(i->second->GetDestinationState());
            auto newNode = std::make_shared<Node>(newState);
            for (auto j : closeList)
            {
                if (newNode->state == j.begin()->get()->state)
                {
                    skip = true;
                    break;
                }
            }
            if (skip)continue;
            newNode->g = currentG + 1;
            newNode->h = -(newNode->state->expectation - exp->expectation);
            newNode->f = newNode->g + newNode->h;
            //newNode.f = newNode.g;

            std::forward_list<std::shared_ptr<Node>> currentNodeCopy(currentNode);
            currentNodeCopy.emplace_front(newNode);
            openList.emplace_back(currentNodeCopy);
        }
    }
    return result;
}
}