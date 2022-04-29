#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Function/Render/Interface/VertexArray.h"
namespace Stone
{
    class RenderAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
        };
        static API getAPI();
        static std::unique_ptr<RenderAPI> create();
        virtual void clear() = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void init() = 0;
        virtual void drawElements(std::shared_ptr<VertexArray> vertexArray, uint32_t indexCount = 0) = 0;
    private:
        static API s_API;
    };
}