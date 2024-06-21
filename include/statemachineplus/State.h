/*
 * State.h
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

#ifndef LANGUAGE_STATE_H
#define LANGUAGE_STATE_H

#include "AbstractComponent.h"
#include <functional>

namespace statemachineplus {
    using  StateUpdateFunction = std::function<void(float)>;
    class State :public AbstractComponent
    {
    public:
        explicit State(StateUpdateFunction updateFunction) {
            func = std::move(updateFunction);
        }
        ~State()override = default;
        void Update(float dt) override {
            if (func != nullptr)
                func(dt);
        }
        void GetActiveComponentArr(std::vector<std::string>& arr) override{};
        std::string Print(int index)override {
            return "[State\n]";
        }
        int expectation=0;
    protected:
        StateUpdateFunction func;
    };
}



#endif //LANGUAGE_STATE_H
