#include "AssimpScene.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <Core/FileSystem/Utils.h>
#include <glm/gtc/matrix_transform.hpp>
namespace Stone
{
	AssimpScene::AssimpScene(const std::string& filename)
	{
		// assimp load
		m_Path = filename;
		m_Directory = getDirectoryPath(filename);
		m_AssimpScene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
		// assimp scene meshes
		for (size_t i = 0; i < m_AssimpScene->mNumMeshes; i++)
		{
			const aiMesh* mesh = m_AssimpScene->mMeshes[i];
			m_Meshs.push_back(std::make_shared<AssimpMesh>(mesh, m_AssimpScene, this));
		}

		// Root node
		memcpy(&m_GlobalInverseTransform, &m_AssimpScene->mRootNode->mTransformation, sizeof(float) * 4 * 4);
		m_GlobalInverseTransform = glm::inverse(m_GlobalInverseTransform);
		m_RootNode = std::make_shared<AssimpNode>(nullptr, this, m_AssimpScene->mRootNode, m_AssimpScene);
		m_BoneTransform.reserve(m_BoneOffset.size());
		for (size_t i = 0; i < m_BoneOffset.size(); i++)
		{
			m_BoneTransform.push_back(glm::mat4(1));
		}
		glm::mat4 aaa;
		readNodeHierarchy(0, m_AssimpScene->mRootNode, aaa);
		// release scene
		//aiReleaseImport(scene);
	}
	void AssimpScene::readNodeHierarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform)
	{
		std::string NodeName(pNode->mName.data);

		const aiAnimation* pAnimation = m_AssimpScene->mAnimations[0];

		glm::mat4 NodeTransformation = glm::mat4(1);
		memcpy(&NodeTransformation, &pNode->mTransformation, sizeof(float) * 4 * 4);

		const aiNodeAnim* pNodeAnim = findNodeAnim(pAnimation, NodeName);

		if (pNodeAnim) {
			LOG_DEBUG("pNodeAnim")
			// Interpolate scaling and generate scaling transformation matrix
			aiVector3D Scaling;
			calcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
			glm::mat4 ScalingM = glm::scale(glm::mat4(1), { Scaling.x, Scaling.y, Scaling.z });

			// Interpolate rotation and generate rotation transformation matrix
			aiQuaternion RotationQ;
			calcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
			glm::mat4 RotationM = glm::mat4(1);
			memcpy(&RotationM, &RotationQ.GetMatrix(), sizeof(float) * 4 * 4);

			// Interpolate translation and generate translation transformation matrix
			aiVector3D Translation;
			calcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
			glm::mat4 TranslationM = glm::translate(glm::mat4(1), { Translation.x, Translation.y, Translation.z });
			
			// Combine the above transformations
			NodeTransformation = TranslationM * RotationM * ScalingM;
		}
		glm::mat4 GlobalTransformation = ParentTransform * NodeTransformation;

		if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
			uint32_t BoneIndex = m_BoneMapping[NodeName];
			m_BoneTransform[BoneIndex] = m_GlobalInverseTransform * GlobalTransformation * m_BoneOffset[BoneIndex];
		}

		for (size_t i = 0; i < pNode->mNumChildren; i++) {
			readNodeHierarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
		}
		/*
		if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
			uint BoneIndex = m_BoneMapping[NodeName];
			m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
		}

		for (uint i = 0; i < pNode->mNumChildren; i++) {
			ReadNodeHierarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
		}*/
	}
	void AssimpScene::calcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
	}
	void AssimpScene::calcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
	}
	void AssimpScene::calcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
	}
	const aiNodeAnim* AssimpScene::findNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
	{
		for (size_t i = 0; i < pAnimation->mNumChannels; i++) {
			const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

			if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
				return pNodeAnim;
			}
		}
		return nullptr;
	}
	void AssimpScene::boneTransform(float TimeInSeconds, std::vector<glm::mat4>& Transforms)
	{
	}
}