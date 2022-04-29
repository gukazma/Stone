#pragma once
#include <entt/entt.hpp>
#include "Core/Base/PublicSingleton.h"
#include "Core/Base/macro.h"
#include "Function/Scene/Camera.h"
namespace Stone
{
	class SceneObject;
	class Scene : public PublicSingleton<Scene>
	{
		friend class SceneObject;
	public:
		Scene();
		~Scene() = default;

        void renderTick();

        void initialize();
		SceneObject CreateObject(const std::string& name = std::string());
	private:
		entt::registry m_Registry;
        Camera* m_CurrentCamera;
	};

    class SceneObject
    {
    public:
        Scene* m_Scene = nullptr;
    public:
        SceneObject() = default;
        ~SceneObject() = default;
        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            ASSERT(!HasComponent<T>(), " SceneObject has the component!");
            T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        T& GetComponent()
        {
            ASSERT(HasComponent<T>(), "Entity doesn't has component");
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent()
        {
            ASSERT(HasComponent<T>(), "Entity does not have component!");
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        SceneObject(const entt::entity& handle, Scene* scene)
            : m_EntityHandle(handle), m_Scene(scene)
        {}

        operator uint32_t() const { return (uint32_t)m_EntityHandle; }
        bool operator==(const SceneObject& other) const { return other.m_EntityHandle == m_EntityHandle; }
        operator bool() const { return m_EntityHandle != entt::null; }
        operator entt::entity() const { return m_EntityHandle; }

        entt::entity m_EntityHandle{ entt::null };
    };
}