#pragma once
#include <vector>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <memory>
namespace Stone
{
	class AssimpScene;
	class AssimpMesh;
	class AssimpNode
	{
	public:
		AssimpNode(const AssimpNode* parentNode, const AssimpScene* assimpscene, const aiNode* node, const aiScene* scene);

	private:

		void loadNode(const aiScene* scene, const aiNode* node);

		std::vector<std::shared_ptr<AssimpMesh>> m_ChildMeshes;
		std::vector<std::shared_ptr<AssimpNode>> m_ChildNodes;

		glm::mat4 m_Transform;

		const AssimpNode* m_Parent;
		const AssimpScene* m_AssimpScene;

		std::string m_NodeName;
	};
}