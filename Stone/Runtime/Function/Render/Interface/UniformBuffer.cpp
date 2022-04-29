#include "Function/Render/Interface/UniformBuffer.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Core/Base/macro.h"
#include "Function/Render/Implement/OpenGL/OpenGLUniformBuffer.h"
namespace Stone
{
    std::shared_ptr<UniformBuffer> UniformBuffer::create(uint32_t size)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLUniformBuffer>(size);
            break;
        default:
            break;
        }
        return nullptr;
    }
}
