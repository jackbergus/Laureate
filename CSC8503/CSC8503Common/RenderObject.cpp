#include "RenderObject.h"

#include "Transform.h"
#include "../../Common/MeshGeometry.h"

using namespace NCL::CSC8503;
using namespace NCL;

RenderObject::RenderObject(Transform* parentTransform, MeshGeometry* mesh, TextureBase* tex, ShaderBase* shader, Vector3 off) {
	this->mesh		= mesh;
	this->texture	= tex;
	this->shader	= shader;
	this->colour	= Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	auto renderTrans = new Transform();
	renderTrans->SetOrientation(parentTransform->GetOrientation());
	renderTrans->SetScale(parentTransform->GetScale());
	renderTrans->SetPosition(parentTransform->GetPosition() - off);
	this->transform = renderTrans;
}

RenderObject::~RenderObject() {

}