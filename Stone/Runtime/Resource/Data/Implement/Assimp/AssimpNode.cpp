#include "AssimpNode.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#include <Function/Render/Renderer.h>

namespace Stone
{
	AssimpNode::AssimpNode(const std::string& filename)
		: m_Filename(filename)
	{
		m_Parent = nullptr;
		const aiScene* scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
		m_Scene = scene;
		loadNode(scene, scene->mRootNode);
	}
	AssimpNode::AssimpNode(AssimpNode* parentNode,const aiNode* node, const	aiScene* scene, const std::string& filename)
		: m_Scene(scene), m_Parent(parentNode), m_Filename(filename), m_Node(node)
	{
		loadNode(scene, node);
	}

	void AssimpNode::recusiveRender(AssimpNode* node)
	{
		for (auto mesh : node->m_ChildMeshes)
		{
			if (mesh->m_Texture != nullptr)
			{
				mesh->m_Texture->bind(0);
			}
			else
			{
				PublicSingleton<TexturePool>::getInstance().getTexture("whiteTexture")->bind(0);
			}
			PublicSingletonInstance(Renderer).render(mesh.get());
		}
		for (auto child : node->m_ChildNodes)
		{
			recusiveRender(child.get());
		}
	}

	void AssimpNode::loadNode(const aiScene* scene, const aiNode* node)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_ChildMeshes.push_back(std::make_shared<AssimpMesh>(mesh, scene, node, m_Filename));
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			m_ChildNodes.push_back(std::make_shared<AssimpNode>(this, node->mChildren[i], scene, m_Filename));
		}
	}
}