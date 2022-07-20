#pragma once
#include <stack>
#include <vector>
/*
 * ����Ӧϵͳ
 *
 * ������������  �����ʹ���
 *
 * ������ �������е������� �������ָ���ǹ��� Debug״̬�� �� ��ɵĻ���
 *
 * ���� ��Ҫ���۲�ĸ��� ����ָ���� ����״̬��������������������ʱ����Ҫ����ע)
 */
namespace NCL {
	namespace CSC8599
	{
		class State;
		class StateMachine;
		using Path = std::stack<State*>;
		using Environment = std::pair<std::string,std::vector<StateMachine*>>;
		using EnvContainer = std::vector<Environment*>;
		class AdaptiveDebugSystem
		{
		public:
			static AdaptiveDebugSystem* getInstance()
			{
				if(instance==nullptr)
				{
					instance = new AdaptiveDebugSystem();
				}
				return instance;
			}
			void insert(Environment* env);
			void update(float dt);
		protected:
			EnvContainer env_container_;
		private:
			static AdaptiveDebugSystem* instance;
			AdaptiveDebugSystem();
			void adjust(Path path, StateMachine* state_machine);
			Environment* find_deadlock_env();
			Path re_plan(StateMachine* state_machine);
		};
	}
}


