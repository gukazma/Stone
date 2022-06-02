#pragma once
#include <Core/Base/PublicSingleton.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
namespace Stone
{
#define MAX_PARTICLE_NUM 1000
	struct Particle
	{
		float Type = 0.0f;
		glm::vec3 Position;
	};

	class ParticleSystemInterface
	{
	public:
		static std::shared_ptr<ParticleSystemInterface> create();
		virtual void logictick() = 0;
		virtual void rendertick() = 0;
		virtual void add(const std::vector<Particle>& particles) = 0;
		virtual void add(const Particle& particle) = 0;
	};

	class ParticleSystem : PublicSingleton<ParticleSystem>
	{
	public:
		void init();

		void add(std::vector<Particle> particles);
		void add(const Particle particle);
		void logictick();
		void rendertick();
	private:
		std::shared_ptr<ParticleSystemInterface> m_ParticleImple;
	};
}