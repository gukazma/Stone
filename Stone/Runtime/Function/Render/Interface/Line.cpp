#include "Line.h"
#include <glad/glad.h>
namespace Stone
{
	Line::Line()
	{
		m_UniformBufferData.isLine = 1;
		m_UniformBuffer = UniformBuffer::create(sizeof(UniformBufferData));
	}
	void Line::enable()
	{
		m_UniformBufferData.isLine = 1;
		m_UniformBuffer->setData(&m_UniformBufferData, sizeof(m_UniformBufferData));
		m_UniformBuffer->bind(3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(40.0f, -10.0f);
	}
	void Line::disable()
	{
		m_UniformBufferData.isLine = 0;
		m_UniformBuffer->setData(&m_UniformBufferData, sizeof(m_UniformBufferData));
		m_UniformBuffer->bind(3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
}