#pragma once
#include "Function/Render/Texture.h"

#include <glad/glad.h>
namespace Stone
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);

        void bind(uint32_t slot) override;

        void setData(void* data, uint32_t size) override;

        uint32_t getRendererID() override;
    private:
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
        uint32_t m_Width, m_Height;
    };
}