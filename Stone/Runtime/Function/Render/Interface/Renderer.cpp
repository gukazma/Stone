#include "Function/Render/Interface/Renderer.h"
#include "Function/Scene/EditCamera.h"

#include "Function/Render/Implement/OpenGL/OpenGLRenderer.h"
#include <glad/glad.h>
namespace Stone
{
	Renderer::Renderer()
	{
		m_RendererImp = RendererInterface::create();
	}
	void Renderer::initialize()
	{
		m_RendererImp->initialize();
	}
	void Renderer::begin()
	{
		m_RendererImp->begin();
	}
	void Renderer::end(uint32_t defaultFramebuffer)
	{
		m_RendererImp->end(defaultFramebuffer);
	}
	void Renderer::render(const Mesh* mesh)
	{
		m_RendererImp->render(mesh);
	}

	std::shared_ptr<RendererInterface> RendererInterface::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			ASSERT(false, "RenderAPI is None")
				break;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLRenderer>();
			break;
		default:
			break;
		}
		return nullptr;
	}
}