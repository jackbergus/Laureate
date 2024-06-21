/*
 * AbstractComponent.h
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

#ifndef LANGUAGE_ABSTRACTCOMPONENT_H
#define LANGUAGE_ABSTRACTCOMPONENT_H

#include <string>
#include <vector>

namespace statemachineplus {

    class AbstractComponent
    {
    public:
        AbstractComponent() = default;
        virtual~AbstractComponent() = default;
        virtual void Update(float dt) = 0;
        virtual std::string Print(int index) = 0;
        virtual void GetActiveComponentArr(std::vector<std::string>& arr)=0;
    };

} // debugstatemachine

#endif //LANGUAGE_ABSTRACTCOMPONENT_H
