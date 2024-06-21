/*
 * AbstractStateMachine.h
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

#ifndef LANGUAGE_ABSTRACTSTATEMACHINE_H
#define LANGUAGE_ABSTRACTSTATEMACHINE_H

#include <memory>
#include <debugstatemachine/AbstractComponent.h>
#include <map>

namespace statemachineplus {

    using ContainerIterator = std::map<std::string, std::shared_ptr<AbstractComponent>>::iterator;
    class AbstractStateMachine :public AbstractComponent
    {
    public:
        AbstractStateMachine() = default;
        ~AbstractStateMachine()override = default;
        void AddComponent(const std::string&, std::shared_ptr<AbstractComponent>);
        std::shared_ptr<AbstractComponent> GetComponent(const std::string&);

        inline std::map<std::string, std::shared_ptr<AbstractComponent>> get_component_container() const
        {
            return ComponentContainer;
        }
    protected:
        std::map<std::string, std::shared_ptr<AbstractComponent>> ComponentContainer;
    };

} // debugstatemachine

#endif //LANGUAGE_ABSTRACTSTATEMACHINE_H
