#include "GameObject.h"
#include "CollisionDetection.h"
#include "../../CSC8599Common/EventSystem.h"
using namespace NCL::CSC8503;

GameObject::GameObject(string objectName)	{
	name			= objectName;
	worldID			= -1;
	isActive		= true;
	boundingVolume	= nullptr;
	physicsObject	= nullptr;

	renderObject = nullptr;
	layers = Default;
	register_handlers();
}

GameObject::~GameObject()	{
	delete boundingVolume;
	delete physicsObject;
	delete renderObject;
}

bool GameObject::GetBroadphaseAABB(Vector3&outSize) const {
	if (!boundingVolume) {
		return false;
	}
	outSize = broadphaseAABB;
	return true;
}

void GameObject::UpdateBroadphaseAABB() {//Ҫ���������͵���ײ��ת��ΪAABB���͵���ײ��
	if (!boundingVolume) {
		return;
	}
	if (boundingVolume->type == VolumeType::AABB) {
		broadphaseAABB = ((AABBVolume&)*boundingVolume).GetHalfDimensions();
	}
	else if (boundingVolume->type == VolumeType::Sphere) {
		float r = ((SphereVolume&)*boundingVolume).GetRadius();
		broadphaseAABB = Vector3(r, r, r);
	}
	else if (boundingVolume->type == VolumeType::OBB) {
		Matrix3 mat = Matrix3(transform.GetOrientation());
		mat = mat.Absolute();
		Vector3 halfSizes = ((OBBVolume&)*boundingVolume).GetHalfDimensions();
		broadphaseAABB = mat * halfSizes;
	}
}

void GameObject::register_handlers()
{
	EventSystem::Get()->RegisterEventHandler("ThreatChanged", [this](EVENT* p_event)->void
	{
			int id = stoi(p_event->vArg[0]);
			if (id == GetWorldID())
				GetRenderObject()->SetColour(Vector4(0, 0, 1, 1));
			else
				GetRenderObject()->SetColour(Vector4(1, 1, 1, 1));
	});
}
