#include "Function/Render/Renderer.h"
#include "Function/Scene/EditCamera.h"

#include "Platform/OpenGL/OpenGLRenderer.h"

#include "Resource/Data/Interface/Mesh.h"
#include <glad/glad.h>
#include "Line.h"
#include "Engine.h"

namespace Stone
{
	Renderer::Renderer()
	{
		m_RendererImp = RendererInterface::create();
	}
	void Renderer::initialize()
	{
		m_RendererImp->initialize();
		m_TimeBuffer = UniformBuffer::create();
	}
	void Renderer::begin()
	{
		m_RendererImp->begin();
		updateDeltaTime();
	}
	void Renderer::end(uint32_t defaultFramebuffer)
	{
		m_RendererImp->end(defaultFramebuffer);
	}
	void Renderer::render(Mesh* mesh)
	{
		mesh->updateBuffer();
		m_RendererImp->render(mesh);
	}
	void Renderer::render(Billboard* billboard)
	{
		billboard->update();
		m_RendererImp->render(billboard);
	}
	void Renderer::renderLine(Mesh* mesh)
	{
		PublicSingletonInstance(Line).enable();
		render(mesh);
		PublicSingletonInstance(Line).disable();
	}

	void Renderer::updateDeltaTime()
	{
		float deltaTime = PublicSingleton<Engine>::getInstance().DeltaTime;
		m_TimeData.DeltaTime = deltaTime;
		m_TimeData.GlobalTime += deltaTime;
		m_TimeBuffer->setData(&m_TimeData, sizeof(m_TimeData));
		m_TimeBuffer->bind(4);
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