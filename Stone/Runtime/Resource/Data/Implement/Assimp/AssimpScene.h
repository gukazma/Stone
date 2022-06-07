#pragma once
#include <vector>
#include <memory>
#include <string>
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
	private:
		std::shared_ptr<AssimpNode> m_RootNode;
		std::vector<std::shared_ptr<AssimpMesh>> m_Meshs;

		std::string m_Path;
		std::string m_Directory;
	};
}