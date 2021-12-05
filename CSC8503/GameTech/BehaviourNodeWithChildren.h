#pragma once
#include "BehaviourNode.h"
#include <vector>
//��һЩ�ڵ����������ӽڵ�
class BehaviourNodeWithChildren:public BehaviourNode
{
public:
	BehaviourNodeWithChildren(const std::string& nodeName) 
		:BehaviourNode(nodeName) {};//�����ǳ�ʼ���б� �Ը�����г�ʼ��
	~BehaviourNodeWithChildren() {
		for (auto& i : childNodes) {
			delete i;
		}
	}
	void AddChild(BehaviourNode* n) {
		childNodes.emplace_back(n);//  C++ 11 �����ӵ� emplace_back push_back���ȴ������Ԫ���ٰ��������������� emplaceʡȥ�˴������ƶ��Ĺ���
	}
	void Reset() override {
		currentState = Initialise;
		for (auto& i : childNodes) {
			i->Reset();
		}
		
	}
protected:
	std::vector<BehaviourNode*> childNodes;
};

