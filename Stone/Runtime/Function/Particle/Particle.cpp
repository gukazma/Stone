#include "Particle.h"
#include "Function/Render/RenderAPI.h"

#include "Platform/OpenGL/OpenGLParticle.h"
namespace Stone
{
	void ParticleSystem::init()
	{
		m_ParticleImple = ParticleSystemInterface::create();
	}
	void ParticleSystem::add(std::vector<Particle> particles)
	{
		m_ParticleImple->add(particles);
	}
	void ParticleSystem::add(const Particle particle)
	{
		m_ParticleImple->add(particle);
	}
	void ParticleSystem::logictick()
	{
		m_ParticleImple->logictick();
	}
	void ParticleSystem::rendertick()
	{
		m_ParticleImple->rendertick();
	}
	std::shared_ptr<ParticleSystemInterface> ParticleSystemInterface::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			ASSERT(false, "RenderAPI is None")
				break;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLParticle>();
			break;
		default:
			break;
		}
		return nullptr;
	}
}