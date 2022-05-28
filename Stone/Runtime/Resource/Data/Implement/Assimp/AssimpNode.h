#pragma once
#include <vector>
#include "AssimpMesh.h"

#include <assimp/scene.h>

#include <glm/glm.hpp>
namespace Stone
{
	class AssimpNode
	{
	public:
		AssimpNode(const std::string& filename);

		AssimpNode(AssimpNode* parentNode, const aiNode* node, const aiScene* scene, const std::string& filename);

		static void recusiveRender(AssimpNode* node);
	public:

		void loadNode(const aiScene* scene, const aiNode* node);

		std::vector<std::shared_ptr<AssimpMesh>> m_ChildMeshes;
		std::vector<std::shared_ptr<AssimpNode>> m_ChildNodes;

		glm::mat4 m_Transform;

		const aiScene* m_Scene;
		const aiNode* m_Node;
		const AssimpNode* m_Parent;

		std::string m_Filename;
	};
}