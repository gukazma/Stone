#pragma once
#include <Function/Render/Texture.h>
#include <Function/Render/VertexArray.h>
#include <glm/glm.hpp>
#include <vector>
namespace Stone
{
	class Billboard
	{
	public:
		Billboard(const std::vector<glm::vec3>& vPos, const std::string& texturepath);

		void update();
		static void Render(Billboard* billboard);
	public:
		std::vector<glm::vec3> m_VPos;
		bool m_IsNeedUpdate = true;
		std::string m_TexturePath;
		std::shared_ptr<VertexBuffer> m_VBO = nullptr;
		std::shared_ptr<VertexArray> m_VAO = nullptr;
		std::shared_ptr<Texture2D> m_Texture = nullptr;
	};
}