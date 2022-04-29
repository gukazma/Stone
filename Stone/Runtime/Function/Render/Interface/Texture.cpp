#include "Function/Render/Interface/Texture.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Core/Base/macro.h"

#include "Function/Render/Implement/OpenGL/OpenGLTexture.h"
namespace Stone
{
    std::shared_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(width, height);
            break;
        default:
            break;
        }
        return nullptr;
    }
    std::shared_ptr<Texture2D> Texture2D::create(const std::string& path)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);
            break;
        default:
            break;
        }
        return nullptr;
    }
}
