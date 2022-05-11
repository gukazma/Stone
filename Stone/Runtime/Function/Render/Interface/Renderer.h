#pragma once
#include "Core/Base/PublicSingleton.h"
#include "Function/Scene/Camera.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Function/Render/Interface/FrameBuffer.h"
#include "Resource/Data/Interface/Mesh.h"
namespace Stone
{

	class RendererInterface
	{
		friend class Renderer;
	public:

		static std::shared_ptr<RendererInterface> create();
		virtual void initialize() = 0;
		virtual void begin() = 0;
		virtual void end(uint32_t defaultFramebuffer) = 0;
		virtual void render(const Mesh* mesh) = 0;
		virtual std::shared_ptr<FrameBuffer> screenFrameBuffer() = 0;

	};

	class Renderer : public PublicSingleton<Renderer>
	{
	public:

		Renderer();

		void initialize();
		void begin();
		void end(uint32_t defaultFramebuffer);

		void render(Mesh* mesh);

		void renderLine(Mesh* mesh);
		std::unique_ptr<RenderAPI> API;

		std::shared_ptr<FrameBuffer> screenFrameBuffer() { return m_RendererImp->screenFrameBuffer(); }
	private:

		std::shared_ptr<RendererInterface> m_RendererImp;
	};

	
}