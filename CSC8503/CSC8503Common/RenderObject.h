#pragma once
#include "../../Common/Matrix4.h"
#include "../../Common/TextureBase.h"
#include "../../Common/ShaderBase.h"
#include "../../Common/Vector4.h"
#include "../../Common/Vector3.h"
/*
��ȾĿ����Ҫ�ṩ �����塢��ͼ��shader���任����ɫ
��Ϊ����ʹ�õ��Ǽ򵥵Ĺ���ģ�� ������ͼû��ָ��Bump��ͼ�Ĳ��� ���ڸ��Ƶ���Ϸ��������ͼҲ��ᱻ������һ��ָ����ϵ�ָ�����飩
*/
namespace NCL {
	using namespace NCL::Rendering;

	class MeshGeometry;
	namespace CSC8503 {
		class Transform;
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject(Transform* parentTransform, MeshGeometry* mesh, TextureBase* tex, ShaderBase* shader,Vector3 off=Vector3(0,0,0));
			~RenderObject();

			void SetDefaultTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetDefaultTexture() const {
				return texture;
			}

			MeshGeometry*	GetMesh() const {
				return mesh;
			}

			Transform*		GetTransform() const {
				return transform;
			}

			ShaderBase*		GetShader() const {
				return shader;
			}

			void SetColour(const Vector4& c) {
				colour = c;
			}

			Vector4 GetColour() const {
				return colour;
			}
		protected:
			MeshGeometry*	mesh;
			TextureBase*	texture;
			ShaderBase*		shader;
			Transform*		transform;
			Vector4			colour;//��ɫ������� ������屻����������巢����ײ��ʱ�� ������Ӧ
		};
	}
}
