#include "Function/Render/RenderAPI.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"
#include "Core/Base/macro.h"

namespace Stone
{
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

    RenderAPI::API RenderAPI::getAPI()
    {
        return s_API;
    }

    std::unique_ptr<RenderAPI> RenderAPI::create()
    {
        switch (s_API)
        {
        case API::None:
            LOG_ERROR("RenderAPI is None");
            break;
        case API::OpenGL:
            return std::make_unique<OpenGLRenderAPI>();
            break;
        default:
            break;
        }
        LOG_ERROR("API is not defined!");
        return nullptr;
    }
}

