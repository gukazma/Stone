#pragma once
#include "Function/Render/Interface/Shader.h"
#include <string>
namespace Stone
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name);
        virtual ~OpenGLShader();
        void link(const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize, const uint32_t* gsshader = nullptr, size_t gssize = 0) override;
        void bind() override;
        void unbind() override;
        void setMat4(const std::string &name, const glm::mat4& value) const override;
        virtual void setInt(const std::string &name, uint32_t value) const override;
    private:
        int checkCompileErrors(unsigned int shader, std::string type);
        uint32_t m_RendererID;
        std::string m_Name;
    };
}