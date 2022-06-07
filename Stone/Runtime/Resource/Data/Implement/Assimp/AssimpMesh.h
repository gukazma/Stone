#pragma once

#include <Resource/Data/Interface/Mesh.h>
#include <Function/Render/Texture.h>
#include <vector>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include <memory>
#include "AssimpScene.h"
namespace Stone
{
	class AssimpMesh : public Mesh
	{
	public:
		struct BoneIndexRefer
		{
			uint32_t currentBoneIndex = 0;
		};
		AssimpMesh(const aiMesh* mesh, const aiScene* scene, const AssimpScene* assmipscene);

		std::vector<std::shared_ptr<AssimpMesh>> m_Children;
		std::shared_ptr<Texture2D> m_Texture = nullptr;
	private:
		void loadMesh(const aiMesh* mesh);

		void loadTexture(const aiMesh* mesh, const aiScene* scene);

		virtual void updateBuffer() override;
        
        bool m_NeedUpdateBuffer = true;

		BoneIndexRefer* m_BoneIndexRefer = nullptr;
	};
}