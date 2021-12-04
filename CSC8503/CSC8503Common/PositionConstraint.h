#pragma once
#include "Constraint.h"
#include "../../Common/Vector3.h"
#include "GameObject.h"
using namespace NCL;
using namespace CSC8503;
using namespace Maths;
class PositionConstraint :public Constraint
{
public:
	PositionConstraint(GameObject* a, GameObject* b, float d) {
		objectA = a;
		objectB = b;
		distance = d;
	
	}
	~PositionConstraint() {}

	void UpdateConstraint(float dt) override {
		Vector3 relativePos = objectA->GetTransform().GetPosition() -
			objectB->GetTransform().GetPosition();
		float currentDistance = relativePos.Length();

		float offset = distance - currentDistance;// contraint= Լ������-���ڵľ���

		if (abs(offset) > 0.0f) {//������Լ��������   
			Vector3 offsetDir = relativePos.Normalised();//��Եķ���

			PhysicsObject* physA = objectA->GetPhysicsObject();
			PhysicsObject* physB = objectB->GetPhysicsObject();

			Vector3 relativeVelocity = physA->GetLinearVelocity() - physB->GetLinearVelocity();//��Ե��ٶ�

			float constraintMass = physA->GetInverseMass() + physB->GetInverseMass();//������inverse

			if (constraintMass > 0.0f) {
				float velocityDot = Vector3::Dot(relativeVelocity, offsetDir);   //C=J*v  ���Ҫ��������Լ����jacobian������λ�õ�Լ�� ʵ�����Ǽ�������ٶȵ�Լ��
				float biasFactor = 0.01f;
				float bias = -(biasFactor / dt) * offset;

				float lambad = -(velocityDot + bias) / constraintMass;//������������           lambad=1/inverseMass*Jacobian*velocity

				Vector3 aImpulse = offsetDir * lambad;//��
				Vector3 bImpulse = -offsetDir * lambad;

				physA->ApplyLinearImpulse(aImpulse);
				physB->ApplyLinearImpulse(bImpulse);

			}
		}

	}
protected:
	GameObject* objectA;//ǰһ����Ҫ����Լ��������
	GameObject* objectB;//��һ����Ҫ����Լ��������
	float distance;//λ����Ҫ�����Լ��

};



