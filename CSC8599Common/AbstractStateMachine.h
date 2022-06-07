#pragma once
#include "AbstractComponent.h"
#include <map>
namespace NCL {
	namespace CSC8599 {
		using ContainerIterator = std::map<std::string, AbstractComponent*>::iterator;
		class AbstractStateMachine :public AbstractComponent
		{
		public:
			AbstractStateMachine() = default;
			~AbstractStateMachine()override = default;
			void AddComponent(const std::string&, AbstractComponent*);
			AbstractComponent* GetComponent(const std::string&);
		protected:
			std::map<std::string, AbstractComponent*> ComponentContainer;
		};
	}
}
