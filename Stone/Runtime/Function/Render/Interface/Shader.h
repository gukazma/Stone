#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include "Core/Base/PublicSingleton.h"
namespace Stone
{
    class Shader
    {
    public:
        enum class ShaderType
        {
            Vertex_Shader = 0,
            Geometry_Shader,
            Fragment_Shader
        };
        virtual ~Shader() = default;
        virtual uint32_t create(const uint32_t* shaderSource, size_t shadersize, ShaderType shaderType) = 0;
        virtual void deleteShader(uint32_t shaderid) = 0;
        virtual void attach(uint32_t shader) = 0;
        virtual void link() = 0;
        virtual void link(const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize, const uint32_t* gsshader = nullptr, size_t gssize = 0) = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        static std::shared_ptr<Shader> create(const std::string&);
        virtual void setMat4(const std::string &name, const glm::mat4& value) const = 0;
        virtual void setInt(const std::string &name, uint32_t value) const = 0;
        virtual uint32_t getRenderID()const = 0;
    private:
    };

    class ShaderPool : public PublicSingleton<ShaderPool>
    {
    public:
        ShaderPool();

        std::shared_ptr<Shader> add(const std::string& name, const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize, const uint32_t* gsshader = nullptr, size_t gssize = 0);
        std::shared_ptr<Shader> add(const std::string& name, std::shared_ptr<Shader> shader);

        std::shared_ptr<Shader> get(const std::string& name);
    private:
        std::map<std::string, std::shared_ptr<Shader>> m_ShaderMap;
    };
}