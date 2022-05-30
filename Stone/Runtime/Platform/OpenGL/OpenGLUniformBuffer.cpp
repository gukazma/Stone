#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include <glad/glad.h>
namespace Stone
{
    OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
        glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW); // 分配152字节的内存
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void OpenGLUniformBuffer::setData(const void* data, uint32_t size, uint32_t offset)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }

    void OpenGLUniformBuffer::bind(uint32_t binding)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
    }
    void OpenGLUniformBuffer::unbind()
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }
}
