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
        virtual ~Shader() = default;
        virtual void link(const uint32_t* vshader, size_t vsiz,const uint32_t* fshader, size_t fsize) = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        static std::shared_ptr<Shader> create(const std::string&);
        virtual void setMat4(const std::string &name, const glm::mat4& value) const = 0;
        virtual void setInt(const std::string &name, uint32_t value) const = 0;
    private:
    };

    class ShaderPool : public PublicSingleton<ShaderPool>
    {
    public:
        ShaderPool();

        std::shared_ptr<Shader> add(const std::string& name,const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize);

        std::shared_ptr<Shader> get(const std::string& name);
    private:
        std::map<std::string, std::shared_ptr<Shader>> m_ShaderMap;
    };
}