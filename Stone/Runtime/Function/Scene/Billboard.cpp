#include "Billboard.h"
#include <Function/Render/RenderAPI.h>
namespace Stone
{
	Billboard::Billboard(const std::vector<glm::vec3>& vPos, const std::string& texturepath)
		: m_VPos(vPos), m_TexturePath(texturepath)
	{
	}
	void Billboard::update()
	{
		if (!m_IsNeedUpdate)
		{
			return;
		}
		if (m_VAO == nullptr || m_VBO == nullptr)
		{
			m_VAO = VertexArray::create();
			m_VBO = VertexBuffer::create((void*)m_VPos.data(), sizeof(float) * m_VPos.size() * 3);
			m_VBO->setLayout({
			{ ShaderDataType::Float3, "aPos" },
				});
			m_VAO->addVertexBuffer(m_VBO);
			m_Texture = PublicSingleton<TexturePool>::getInstance().getTexture(m_TexturePath);
		}
		else
		{
			m_VBO->setData((void*)m_VPos.data(), sizeof(float) * m_VPos.size() * 3);
		}

		m_IsNeedUpdate = false;
	}
	void Billboard::Render(Billboard* billboard)
	{
		billboard->m_Texture->bind(0);
		
	}
}