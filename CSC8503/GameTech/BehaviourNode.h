#pragma once
#include <string>
enum BehaviourState {
	Initialise,
	Failure,
	Success,
	Ongoing
};

class BehaviourNode
{//�ڵ�ӵ��һ�����ֺ�״̬
public:
	BehaviourNode(const std::string& nodeName) {
		currentState = Initialise;
		name = nodeName;
	}
	virtual ~BehaviourNode() {}
	virtual BehaviourState Execute(float dt) = 0;//���麯��

	virtual void Reset() { currentState = Initialise;}
protected:
	BehaviourState currentState;
	std::string name;
};

