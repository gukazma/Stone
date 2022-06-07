#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include "AssimpNode.h"
#include "AssimpMesh.h"
namespace Stone
{
	class AssimpScene
	{
		friend class AssimpNode;
		friend class AssimpMesh;
		friend class Scene;
	public:
		AssimpScene(const std::string& filename);

		void readNodeHierarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);

	private:
		void calcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void calcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void calcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		const aiNodeAnim* findNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
		void boneTransform(float TimeInSeconds, std::vector<glm::mat4>& Transforms);

		std::shared_ptr<AssimpNode> m_RootNode;
		std::vector<std::shared_ptr<AssimpMesh>> m_Meshs;

		std::map<std::string, uint32_t> m_BoneMapping;
		std::vector<glm::mat4> m_BoneTransform;
		std::vector<glm::mat4> m_BoneOffset;
		glm::mat4 m_GlobalInverseTransform;
		uint32_t m_NumBone;

		std::string m_Path;
		std::string m_Directory;

		const aiScene* m_AssimpScene;
	};
}