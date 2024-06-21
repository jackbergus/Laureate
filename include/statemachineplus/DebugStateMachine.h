/*
 * DebugStateMachine.h
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
// Created by giacomo on 21/06/24.
//

#ifndef LANGUAGE_DEBUGSTATEMACHINE_H
#define LANGUAGE_DEBUGSTATEMACHINE_H

#include <debugstatemachine/StateMachinePlus.h>

namespace statemachineplus {
    class State;
    class DebugStateMachine :public StateMachinePlus
    {
    public:
        DebugStateMachine() {
            //auto A = new StateMachine("0",
            //	new State([this](float dt)->void
            //	{
            //		time_stack = 0.0f;
            //	}));
            //A->AddComponent("1", new State([this](float dt)->void
            //	{
            //		time_stack += dt;
            //		if (time_stack > 1.5f)
            //			EventSystem::getInstance()->PushEvent("Debug_PetTaunt", 0);
            //	}));
            //A->AddTransition(new CSC8599::StateTransition(A->GetComponent("0"), A->GetComponent("1"), [this](EVENT* event)->bool
            //{
            //		return EventSystem::getInstance()->HasHappened("player_over_threat");
            //	/*&&
            //			(EventSystem::getInstance()->HasHappened("player_die")||
            //				!EventSystem::getInstance()->HasHappened("Debug_PetTaunt"))
            //			use LTL_TO_EDGES
            //	*/
            //},""));
            //A->AddTransition(new CSC8599::StateTransition(A->GetComponent("1"), A->GetComponent("0"), [this](EVENT* event)->bool
            //{
            //		return EventSystem::getInstance()->HasHappened("Debug_PetTaunt");
            //	/*&&
            //			!EventSystem::getInstance()->HasHappened("player_die")

            //	*/
            //}, ""));


            //auto B = new StateMachine("2",
            //	new State([this](float dt)->void
            //	{}));

            //B->AddComponent("1", new State([this](float dt)->void
            //{
            //}));
            //B->AddComponent("0", new State([this](float dt)->void
            //	{
            //		EventSystem::getInstance()->PushEvent("Debug_PetDie", 0);
            //	}));

            //B->AddTransition(new CSC8599::StateTransition(B->GetComponent("2"), B->GetComponent("1"), [this](EVENT* event)->bool
            //	{
            //	return EventSystem::getInstance()->HasHappened("player_die");
            //	}, ""));
            //B->AddTransition(new CSC8599::StateTransition(B->GetComponent("1"), B->GetComponent("2"), [this](EVENT* event)->bool
            //	{
            //		return true;
            //	}, "pet_die"));

            //B->AddTransition(new CSC8599::StateTransition(B->GetComponent("1"), B->GetComponent("0"), [this](EVENT* event)->bool
            //	{
            //	return !EventSystem::getInstance()->HasHappened("pet_die");
            //	}, ""));
            //B->AddTransition(new CSC8599::StateTransition(B->GetComponent("0"), B->GetComponent("2"), [this](EVENT* event)->bool
            //	{
            //		return true;
            //	}, "pet_die"));

            //auto state0 = new  State([this](float dt)->void
            //	{

            //	});
            //auto state1=new  State([this](float dt)->void
            //{
            //
            //});

            //auto state2 = new  State([this](float dt)->void
            //	{

            //	});
            //auto state3 = new  State([this](float dt)->void
            //	{

            //	});

            //state1->expectation = 0;
            //state2->expectation = 1;
            //state3->expectation = 2;
            //state0->expectation = 3;

        };
        ~DebugStateMachine() override;
    };

} // debugstatemachine

#endif //LANGUAGE_DEBUGSTATEMACHINE_H
