#include "Function/Scene/Light.h"
#include "Function/Scene/EditCamera.h"
namespace Stone
{
	GLobalLight::GLobalLight()
	{
		m_UniformBuffer = UniformBuffer::create(sizeof(GLobalLight));
		updateBuffer();
	}
	void GLobalLight::bind(uint32_t index)
	{
		m_UniformBuffer->bind(index);
	}
	void GLobalLight::updateBuffer()
	{
		m_UniformBuffer->setData(&m_BlockData, sizeof(UniformBlock));
	}
}