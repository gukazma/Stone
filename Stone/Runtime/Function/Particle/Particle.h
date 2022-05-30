#pragma once
#include <Core/Base/PublicSingleton.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
namespace Stone
{
#define MAX_PARTICLE_NUM 1000
	struct Particle
	{
		float v;
	};

	class ParticleSystemInterface
	{
	public:
		static std::shared_ptr<ParticleSystemInterface> create();
		virtual void logictick() = 0;
		virtual void rendertick() = 0;
		virtual void add(const std::vector<Particle>& particles) = 0;
		virtual void add(const Particle particle) = 0;
	};

	class ParticleSystem : PublicSingleton<ParticleSystem>
	{
	public:
		void init();

		void add(const std::vector<Particle>& particles);
		void add(const Particle particle);
		void logictick();
		void rendertick();
	private:
		std::shared_ptr<ParticleSystemInterface> m_ParticleImple;
	};
}