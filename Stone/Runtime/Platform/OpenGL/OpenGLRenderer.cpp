#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Function/Scene/EditCamera.h"
#include "Function/Render/Shader.h"
#include <glad/glad.h>
namespace Stone
{
	OpenGLRenderer::OpenGLRenderer()
	{
		API = RenderAPI::create();
	}
	void OpenGLRenderer::initialize()
	{
		ASSERT(gladLoadGL(), "glad loadGL failed!");
		glClearColor(0.3, 0.3, 0.3, 1.0);

		// screen offline render
		FrameBufferSpecification spec;
		spec.AttachmentsSpecification = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::Depth };
		spec.Height = 1280;
		spec.Width = 720;
		m_FrameBuffer = FrameBuffer::create(spec);

		float quadVertices[] = {// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
								// positions   // texCoords
								-1.0f, 1.0f, 0.0f, 1.0f,
								-1.0f, -1.0f, 0.0f, 0.0f,
								1.0f, -1.0f, 1.0f, 0.0f,

								-1.0f, 1.0f, 0.0f, 1.0f,
								1.0f, -1.0f, 1.0f, 0.0f,
								1.0f, 1.0f, 1.0f, 1.0f };
		m_QuadVAO = VertexArray::create();
		auto quadVBO = VertexBuffer::create((void*)quadVertices, sizeof(quadVertices));
		quadVBO->setLayout({
			{ ShaderDataType::Float2, "aPos" },
			{ ShaderDataType::Float2, "aTexCoord" }
			});
		m_QuadVAO->addVertexBuffer(quadVBO);
	}
	void OpenGLRenderer::begin()
	{
		m_FrameBuffer->bind();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.3, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderer::end(uint32_t defaultFramebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
		PublicSingleton<ShaderPool>::getInstance().get("ScreenShader")->bind();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_QuadVAO->bind();
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, PublicSingleton<Renderer>::getInstance().screenFrameBuffer()->getColorAttachmentRendererID());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	void OpenGLRenderer::render(const Mesh* mesh)
	{
		mesh->m_VAO->bind();
		API->drawElements(mesh->m_VAO);
	}
	void OpenGLRenderer::render(const Billboard* billboard)
	{
		billboard->m_Texture->bind(0);
		API->drawArrays(billboard->m_VAO, RenderAPI::DrawMode::Point, 0, billboard->m_VPos.size());
	}
}