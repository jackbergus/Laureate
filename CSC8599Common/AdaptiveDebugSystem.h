#pragma once
#include <ostream>
#include <stack>
#include <vector>

#include "StateMachine.h"
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
			friend std::ostream& operator<<(std::ostream& os, const AdaptiveDebugSystem& obj)
			{
				std::string buffer("AdaptiveDebugSystem:\n");
				for(const auto i: obj.env_container_)
				{
					buffer += i->first+":\n";
					for(const auto j:i->second)
					{
						buffer += j->Print(0)+"\n";
					}
				}
				return os << buffer;
			}

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


