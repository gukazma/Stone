/*
 * @Author: ImGili
 * @Description: 
 */
#include "Function/Render/Implement/OpenGL/OpenGLRenderAPI.h"
#include<glad/glad.h>
namespace Stone
{
    void OpenGLRenderAPI::init()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderAPI::drawElements(std::shared_ptr<VertexArray> vertexArray, uint32_t indexCount)
    {
        uint32_t count = indexCount == 0 ? vertexArray->getIndexBuffer()->getCount() : indexCount;
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
