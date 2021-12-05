#pragma once
#include <vector>
#include <map>

namespace NCL {
	namespace CSC8503 {

		class State;
		class StateTransition;

		typedef std::multimap<State*, StateTransition*> TransitionContainer;//ʹ�ÿռ��ģ�嵼���˺ܱ�׾�ı����� ��typedef ��ʡ�˿ռ��ʱ��
		typedef TransitionContainer::iterator TransitionIterator;

		class StateMachine	{
		public:
			StateMachine();//��֤activestate��һ����ȫ�Ŀ�ָ�뿪ʼ
			~StateMachine();//���ٵ�ʱ��Ҫɾ�����е�״̬��ת��

			void AddState(State* s);
			void AddTransition(StateTransition* t);//ʹ��multimap��ʾ״̬��������ͼ���� Դ״̬��ΪMap�ļ� ת��������Ϊֵ

			void Update(float dt);

		protected:
			State * activeState;

			std::vector<State*> allStates;

			TransitionContainer allTransitions;
		};
	}
}