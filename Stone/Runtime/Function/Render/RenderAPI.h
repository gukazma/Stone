#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Function/Render/VertexArray.h"
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

        enum class DrawMode
        {
            Point = 0,
            Line,
            Triangle
        };
        static API getAPI();
        static std::unique_ptr<RenderAPI> create();
        virtual void clear() = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void init() = 0;
        virtual void drawElements(std::shared_ptr<VertexArray> vertexArray, uint32_t indexCount = 0) = 0;
        virtual void drawArrays(std::shared_ptr<VertexArray> vertexArray, DrawMode mode, int begin, int num) = 0;
    private:
        static API s_API;
    };
}