#pragma once

#include <Resource/Data/Interface/Mesh.h>
#include <Function/Render/Texture.h>
#include <vector>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include <memory>
namespace Stone
{
	class AssimpMesh : public Mesh
	{
	public:

		AssimpMesh(const aiMesh* mesh, const aiScene* scene, const aiNode* node, const std::string& filename);

		std::vector<std::shared_ptr<AssimpMesh>> m_Children;
		std::shared_ptr<Texture2D> m_Texture = nullptr;
	private:
		void loadMesh(const aiMesh* mesh);

		void leadTexture();

		virtual void updateBuffer() override;
        
        bool m_NeedUpdateBuffer = true;

		const aiScene* m_Scene;
		const aiNode* m_Node;
		const aiMesh* m_Mesh;

	};
}