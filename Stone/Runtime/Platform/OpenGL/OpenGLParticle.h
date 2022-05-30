#pragma once
#include "Function/Particle/Particle.h"
#include <Function/Render/Buffer.h>
#include <Function/Render/VertexArray.h>
#include <Function/Render/Shader.h>
namespace Stone
{
	class OpenGLParticle : public ParticleSystemInterface
	{
	public:
		OpenGLParticle();
		virtual void logictick() override;
		virtual void rendertick() override;
		virtual void add(const std::vector<Particle>& particles) override;
		virtual void add(const Particle particle) override;
	private:
		bool m_SwapFlag = false;
		bool m_IsFirst = true;
		std::shared_ptr<VertexBuffer> m_VBO1, m_VBO2;
		std::shared_ptr<VertexArray> m_VAO1, m_VAO2;
		std::vector<Particle> m_Particles;
		uint32_t m_Query;
		uint32_t m_Primitives;
		std::shared_ptr<Shader> m_ParticleShader;
	};
}