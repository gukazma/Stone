#include "AssimpScene.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <Core/FileSystem/Utils.h>
namespace Stone
{
	AssimpScene::AssimpScene(const std::string& filename)
	{
		m_Path = filename;
		m_Directory = getDirectoryPath(filename);
		const aiScene* scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
		//m_RootNode = std::make_shared<AssimpNode>(nullptr, this, scene->mRootNode, scene);
		for (size_t i = 0; i < scene->mNumMeshes; i++)
		{
			const aiMesh* mesh = scene->mMeshes[i];
			m_Meshs.push_back(std::make_shared<AssimpMesh>(mesh, scene, this));
		}
	}
}