#include "Platform/OpenGL/OpenGLVertexArray.h"
#include <glad/glad.h>
#include "Core/Base/macro.h"

namespace Stone
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::None:     break;
        case ShaderDataType::Float:    return GL_FLOAT;
        case ShaderDataType::Float2:   return GL_FLOAT;
        case ShaderDataType::Float3:   return GL_FLOAT;
        case ShaderDataType::Float4:   return GL_FLOAT;
        case ShaderDataType::Mat3:     return GL_FLOAT;
        case ShaderDataType::Mat4:     return GL_FLOAT;
        case ShaderDataType::Int:      return GL_INT;
        case ShaderDataType::Int2:     return GL_INT;
        case ShaderDataType::Int3:     return GL_INT;
        case ShaderDataType::Int4:     return GL_INT;
        case ShaderDataType::Bool:     return GL_BOOL;
        }

        ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    void OpenGLVertexArray::bind()
    {
        glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::unbind()
    {
        glBindVertexArray(0);
    }
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }
    void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        // TODO: Add VertexBuffer
        ASSERT(vertexBuffer->getLayout().getElements().size() > 0, "VertexBuffer has no elements, set bufferelement!");
        BufferLayout layout = vertexBuffer->getLayout();
        bind();
        vertexBuffer->bind();
        for (const auto& element : layout)
        {
            switch (element.Type)
            {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            {
                glad_glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribPointer(m_VertexBufferIndex,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    layout.getStride(),
                    (const void*)element.Offset);
                m_VertexBufferIndex++;
                break;
            }
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
            case ShaderDataType::Bool:
            {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribIPointer(m_VertexBufferIndex,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    layout.getStride(),
                    (const void*)element.Offset);
                m_VertexBufferIndex++;
                break;
            }
            default:
                break;
            }
        }

        unbind();
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->bind();
        m_IndexBuffer = indexBuffer;
    }

    const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const
    {
        return m_IndexBuffer;
    }
}
