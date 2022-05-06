#include "Function/Render/Interface/Shader.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Function/Render/Implement/OpenGL/OpenGLShader.h"
#include "Core/Base/macro.h"

#include "mesh_vert.h"
#include "mesh_frag.h"
#include "screenquad_vert.h"
#include "screenquad_frag.h"
#include "tiff_vert.h"
#include "tiff_frag.h"
namespace Stone
{
    std::shared_ptr<Shader> Shader::create(const std::string& name)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            LOG_INFO("Create Shader: {0}", name);
            return std::make_shared<OpenGLShader>(name);
            break;
        default:
            break;
        }
        return nullptr;
    }

    ShaderPool::ShaderPool()
    {
        add("MeshShader", mesh_vert, sizeof(mesh_vert), mesh_frag, sizeof(mesh_frag));
        add("ScreenShader", screenquad_vert, sizeof(screenquad_vert), screenquad_frag, sizeof(screenquad_frag));
        add("TiffShader", tiff_vert, sizeof(tiff_vert), tiff_frag, sizeof(tiff_frag));
    }

    std::shared_ptr<Shader> ShaderPool::add(const std::string& name, const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize)
    {
        std::map<std::string, std::shared_ptr<Shader>>::iterator it = m_ShaderMap.find(name);
        if (it == m_ShaderMap.end())
        {
            m_ShaderMap[name] = Shader::create(name);
            m_ShaderMap[name]->link(vshader, vsiz, fshader, fsize);
        }

        return m_ShaderMap[name];
    }

    std::shared_ptr<Shader> ShaderPool::get(const std::string& name)
    {
        return m_ShaderMap[name];
    }

}
