#pragma once
#include "Core/Base/macro.h"
#include "Core/Base/PublicSingleton.h"

#include "Function/Render/Interface/UniformBuffer.h"
#include <glm/glm.hpp>
#include <map>
namespace Stone
{
	class MaterialInterface
	{
	public:
		class UniformBlock
		{
			glm::vec3 Ambient = { 0.5,	0.5, 0.5 };
			glm::vec3 Diffuse = { 0.8, .8, 0.8 };
			glm::vec3 Specular = { 1.0, 1.0, 1.0 };
			float Shininess = .5;
		};
		virtual void bind(uint32_t index){};
		virtual ~MaterialInterface() = default;
	};
	class BasicMaterial : public MaterialInterface
	{
	public:
		BasicMaterial();
		void bind(uint32_t index);
		void updateBuffer();
	private:
		std::shared_ptr<UniformBuffer> m_UniformBuffer;
		UniformBlock m_BlockData;
	};

	class MaterialPool : public PublicSingleton<MaterialPool>
	{
	public:
		MaterialPool();
		std::shared_ptr<MaterialInterface> getMaterial(const std::string& materialName);
	private:
		std::map<std::string, std::shared_ptr<MaterialInterface>> m_MapterialMap;

	};
}