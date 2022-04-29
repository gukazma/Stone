#include "Scene.h"
#include "Resource/Components/Tag.h"

#include "Function/Event/EventSystem.h"
#include "Function/Scene/EditCamera.h"
#include "Function/Scene/Light.h"

#include "Function/Scene/Material.h"
namespace Stone
{
	Scene::Scene()
	{
		m_CurrentCamera = &PublicSingletonInstance(EditorCamera);
	}
	void Scene::renderTick()
	{
		m_CurrentCamera->bind();
		PublicSingletonInstance(GLobalLight).bind(1);
		PublicSingletonInstance(MaterialPool).getMaterial("BasicMaterial")->bind(2);
	}
	void Scene::initialize()
	{
	}
	SceneObject Scene::CreateObject(const std::string& name)
	{
		SceneObject entity = { m_Registry.create(), this};
		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
}
