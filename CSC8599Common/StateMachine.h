#pragma once
#include "AbstractStateMachine.h"
using namespace NCL::CSC8599;
namespace NCL {
	namespace CSC8599 {
		class StateTransition;
		using TransitionContainer = std::multimap<AbstractComponent*, StateTransition*>;
		using TransitionIterator = TransitionContainer::iterator;
		class StateMachine : public AbstractStateMachine {
		public:
			StateMachine(const std::string& name, AbstractComponent* defaultComponent)
				:activeComponent(defaultComponent), ResetComponent(defaultComponent) {
				AddComponent(name, defaultComponent);

			}
			~StateMachine() override { delete activeComponent; activeComponent = nullptr; };
			void Update(float dt) override;
			std::string Print(int index) override;
			void AddTransition(StateTransition* t);
			void GetActiveCompoentArr(std::vector<std::string>& arr) override;
			void SetActiveComponent(AbstractComponent* active)
			{
				activeComponent = active;
			}
			void RollBack(StateTransition* trans);
			TransitionContainer get_all_transitions() const
			{
				return allTransitions;
			}

			void Reset() override;
		protected:
			AbstractComponent* ResetComponent;
			AbstractComponent* activeComponent;
			TransitionContainer allTransitions;
		};
	}
}
