#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Function/Render/Interface/UniformBuffer.h>
namespace Stone
{
    struct TransformComponent {
        TransformComponent() {
            m_UniformBuffer = UniformBuffer::create(sizeof(glm::mat4));
        }
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& translation) : Translation(translation) {}

        glm::mat4 GetTransform() const {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

            return glm::translate(glm::mat4(1.0f), Translation) * rotation *
                glm::scale(glm::mat4(1.0f), Scale);
        }


        void bind(uint32_t index = 2)
        {
            transformMatrix = GetTransform();
            m_UniformBuffer->setData(glm::value_ptr(transformMatrix), sizeof(glm::mat4));

            m_UniformBuffer->bind(index);
        }
    private:
        glm::mat4 transformMatrix = glm::mat4(1);
        std::shared_ptr<UniformBuffer> m_UniformBuffer;
    };
}
