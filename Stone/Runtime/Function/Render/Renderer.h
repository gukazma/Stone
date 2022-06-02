#pragma once
#include "Core/Base/PublicSingleton.h"
#include "Function/Scene/Camera.h"
#include "Function/Render/RenderAPI.h"
#include "Function/Render/FrameBuffer.h"
#include "Resource/Data/Interface/Mesh.h"
#include "Function/Scene/Billboard.h"
#include "Function/Render/UniformBuffer.h"
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
		virtual void render(const Billboard* billboard) = 0;
		virtual std::shared_ptr<FrameBuffer> screenFrameBuffer() = 0;

	};

	class Renderer : public PublicSingleton<Renderer>
	{
	public:
		struct TimeData
		{
			float DeltaTime = 0.0;
			float GlobalTime = 0.0;
		};
		Renderer();

		void initialize();
		void begin();
		void end(uint32_t defaultFramebuffer);

		void render(Mesh* mesh);
		void render(Billboard* billboard);
		void renderLine(Mesh* mesh);
		std::unique_ptr<RenderAPI> API;

		std::shared_ptr<FrameBuffer> screenFrameBuffer() { return m_RendererImp->screenFrameBuffer(); }
	private:
		void updateDeltaTime();
		std::shared_ptr<UniformBuffer> m_TimeBuffer;
		float m_LastDeltaTime = 0.0;
		TimeData m_TimeData;
		std::shared_ptr<RendererInterface> m_RendererImp;
	};

	
}