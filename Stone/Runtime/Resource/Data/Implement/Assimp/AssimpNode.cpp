#include "AssimpNode.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#include <Function/Render/Renderer.h>
#include "AssimpScene.h"
#include "AssimpMesh.h"
namespace Stone
{
	//AssimpNode::AssimpNode(const std::string& filename)
	//{
	//	m_Parent = nullptr;
	//	const aiScene* scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	//	LOG_DEBUG("scene->mNumMeshes: {0}", scene->mNumMeshes)
	//	m_Scene = scene;
	//	for (size_t i = 0; i < scene->mNumMeshes; i++)
	//	{
	//		const aiMesh* mesh = scene->mMeshes[i];
	//		m_ChildMeshes.push_back(std::make_shared<AssimpMesh>(mesh, scene, scene->mRootNode, m_Filename));
	//	}
	//	//loadNode(scene, scene->mRootNode);
	//}
	AssimpNode::AssimpNode(const AssimpNode* parentNode, const AssimpScene* assimpscene, const aiNode* node, const aiScene* scene)
		: m_AssimpScene(assimpscene), m_Parent(parentNode)
	{
		loadNode(scene, node);
	}

	//void AssimpNode::recusiveRender(AssimpNode* node)
	//{
	//	for (auto mesh : node->m_ChildMeshes)
	//	{
	//		if (mesh->m_Texture != nullptr)
	//		{
	//			mesh->m_Texture->bind(0);
	//		}
	//		else
	//		{
	//			PublicSingleton<TexturePool>::getInstance().getTexture("whiteTexture")->bind(0);
	//		}
	//		PublicSingletonInstance(Renderer).render(mesh.get());
	//	}
	//	/*for (auto child : node->m_ChildNodes)
	//	{
	//		recusiveRender(child.get());
	//	}*/
	//}

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