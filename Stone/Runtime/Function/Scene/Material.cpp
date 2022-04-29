#include "Function/Scene/Material.h"

namespace Stone
{
	BasicMaterial::BasicMaterial()
	{
		m_UniformBuffer = UniformBuffer::create(sizeof(UniformBlock));
		updateBuffer();
	}
	void BasicMaterial::bind(uint32_t index)
	{
		m_UniformBuffer->bind(index);
	}
	void BasicMaterial::updateBuffer()
	{
		m_UniformBuffer->setData(&m_BlockData, sizeof(UniformBlock));
	}
	 MaterialPool::MaterialPool()
	{
		 m_MapterialMap["BasicMaterial"] = std::make_shared<BasicMaterial>();
	}
	 std::shared_ptr<MaterialInterface> MaterialPool::getMaterial(const std::string& materialName)
	 {
		 return m_MapterialMap[materialName];
	 }
}