#pragma once
#include "Function/Render/Shader.h"
#include <string>
namespace Stone
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name);
        virtual ~OpenGLShader();
        virtual uint32_t create(const uint32_t* shaderSource, size_t shadersize, ShaderType shaderType) override;
        virtual void deleteShader(uint32_t shaderid) override;
        virtual void attach(uint32_t shader) override;
        virtual void link() override;
        void link(const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize, const uint32_t* gsshader = nullptr, size_t gssize = 0) override;
        void bind() override;
        void unbind() override;
        void setMat4(const std::string &name, const glm::mat4& value) const override;
        virtual void setInt(const std::string &name, uint32_t value) const override;
        virtual uint32_t getRenderID() const override {
            return m_RendererID;
        }
    private:
        int checkCompileErrors(unsigned int shader, std::string type);
        uint32_t m_RendererID;
        std::string m_Name;
    };
}