/*
 * StateMachinePlus.h
 * This file is part of StateMachinePLus
 *
 * Copyright (C) 2022 - Junlin Luo
 *
 * StateMachinePLus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * StateMachinePLus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with StateMachinePLus. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 21/06/24.
//

#ifndef LANGUAGE_STATEMACHINEPLUS_H
#define LANGUAGE_STATEMACHINEPLUS_H

#include <debugstatemachine/AbstractStateMachine.h>

namespace statemachineplus {

    class StateMachinePlus : public AbstractStateMachine {
    public:
        StateMachinePlus() = default;
        ~StateMachinePlus() override = default;
        void Update(float dt) override;
        std::string Print(int index) override;
        void GetActiveComponentArr(std::vector<std::string>& arr) override;
    };
} // debugstatemachine

#endif //LANGUAGE_STATEMACHINEPLUS_H
