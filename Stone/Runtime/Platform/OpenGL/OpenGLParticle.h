#pragma once
#include "Function/Particle/Particle.h"
#include <Function/Render/Buffer.h>
#include <Function/Render/VertexArray.h>
#include <Function/Render/Shader.h>
#include <Function/Render/UniformBuffer.h>
namespace Stone
{
	class OpenGLParticle : public ParticleSystemInterface
	{
	public:
		OpenGLParticle();
		virtual void logictick() override;
		virtual void rendertick() override;
		virtual void add(const std::vector<Particle>& particles) override;
		virtual void add(const Particle& particle) override;
	private:

		void initRandomTexture(uint32_t size);
		void bindRandomTexture(uint32_t index);
		bool m_SwapFlag = true;
		bool m_IsFirst = true;
		std::shared_ptr<VertexBuffer> m_VBO1, m_VBO2;
		std::shared_ptr<VertexArray> m_VAO1, m_VAO2;
		std::vector<Particle> m_Particles;
		uint32_t m_Query;
		uint32_t m_Primitives;
		uint32_t m_RandomTextureId;
		std::shared_ptr<Shader> m_ParticleShader;
		std::shared_ptr<UniformBuffer> m_UniformBuffer;
	};
}