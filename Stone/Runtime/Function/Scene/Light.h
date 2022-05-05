#pragma once
#include <glm/glm.hpp>
#include "Core/Base/PublicSingleton.h"
#include "Function/Render/Interface/UniformBuffer.h"
namespace Stone
{
    class GLobalLight : public PublicSingleton<GLobalLight>
    {
    public:
        struct  UniformBlock
        {
            glm::vec3 Position = { 0.0f, -10.0f, 0.0f };
        };
        GLobalLight();
        void bind(uint32_t index = 0);
        void updateBuffer();
        
        UniformBlock m_BlockData;
    private:
        std::shared_ptr<UniformBuffer> m_UniformBuffer;
    };
}