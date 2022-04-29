#include "Function/Render/Interface/Buffer.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Function/Render/Implement/OpenGL/OpenGLBuffer.h"
namespace Stone
{
    std::shared_ptr<VertexBuffer> VertexBuffer::create(const void* data, uint32_t size)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(data, size);
            break;
        default:
            break;
        }
        return nullptr;
    }
    std::shared_ptr<VertexBuffer> VertexBuffer::create(uint32_t size)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);
            break;
        default:
            break;
        }
        return nullptr;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::create(const uint32_t* indics, uint32_t count)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indics, count);
            break;
        default:
            break;
        }
        return nullptr;
    }
}
