#pragma once
#include "Function/Render/Interface/UniformBuffer.h"

namespace Stone
{
    class OpenGLUniformBuffer : public UniformBuffer
    {
    public:
        OpenGLUniformBuffer(uint32_t size = 152);
        void setData(const void* data, uint32_t size, uint32_t offset = 0) override;
        void bind(uint32_t binding = 0) override;
        void unbind() override;
        ~OpenGLUniformBuffer();
    private:
        uint32_t m_RendererID;
    };
}