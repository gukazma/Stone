#include "AssimpNode.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#include <Function/Render/Renderer.h>
#include "AssimpScene.h"
#include "AssimpMesh.h"
namespace Stone
{
	AssimpNode::AssimpNode(const AssimpNode* parentNode, const AssimpScene* assimpscene, const aiNode* node, const aiScene* scene)
		: m_AssimpScene(assimpscene), m_Parent(parentNode), m_NodeName(node->mName.C_Str())
	{
		 loadNode(scene, node);
	}


	void AssimpNode::loadNode(const aiScene* scene, const aiNode* node)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			std::shared_ptr<AssimpMesh> mesh = m_AssimpScene->m_Meshs[node->mMeshes[i]];
			m_ChildMeshes.push_back(mesh);
		}
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			m_ChildNodes.push_back(std::make_shared<AssimpNode>(this, m_AssimpScene, node->mChildren[i], scene));
		}
	}
}