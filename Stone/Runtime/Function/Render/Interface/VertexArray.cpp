#include "Function/Render/Interface/VertexArray.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Core/Base/macro.h"
#include "Function/Render/Implement/OpenGL/OpenGLVertexArray.h"
namespace Stone
{
    std::shared_ptr<VertexArray> VertexArray::create()
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        default:
            break;
        }
        ASSERT(false, "Renderer API can not create VertexArray!");
        return nullptr;
    }
}
