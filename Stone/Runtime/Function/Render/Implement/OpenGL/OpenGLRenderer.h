#pragma once
#include "Function/Render/Interface/Renderer.h"
#include "Function/Scene/Camera.h"
namespace Stone
{
	class OpenGLRenderer : public RendererInterface
	{
	public:
		OpenGLRenderer();
		void initialize() override;
		void begin() override;
		void end(uint32_t defaultFramebuffer) override;
		void render(const Mesh* mesh) override;
		virtual std::shared_ptr<FrameBuffer> screenFrameBuffer() override { return m_FrameBuffer; }
		std::unique_ptr<RenderAPI> API;
	private:
		std::shared_ptr<FrameBuffer> m_FrameBuffer;
		std::shared_ptr<VertexArray>	m_QuadVAO;
	};
}