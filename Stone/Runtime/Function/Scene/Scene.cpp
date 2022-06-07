#include "Scene.h"
#include "Resource/Components/Tag.h"

#include "Function/Event/EventSystem.h"
#include "Function/Scene/EditCamera.h"
#include "Function/Scene/Light.h"
#include "Function/Scene/Material.h"

#include "Resource/Components/Mesh.h"
#include "Resource/Components/Tag.h"
#include "Resource/Components/Transform.h"
#include "Resource/Data/Implement/VCG/VCGMesh.h"

#include "Function/Render/Renderer.h"
#include "Function/Render/Shader.h"

#include <Resource/Components/Model.h>
#include <Resource/Data/Implement/Assimp/AssimpMesh.h>
#include <Resource/Data/Implement/Assimp/AssimpNode.h>
#include <Resource/Data/Interface/ModelPool.h>

#include <Function/Particle/Particle.h>
#include <Resource/Data/Implement/Assimp/AssimpScene.h>
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
		PublicSingleton<ShaderPool>::getInstance().get("MeshShader")->bind();
		auto view = m_Registry.view<MeshComponent<VCGMesh>, TransformComponent>();
		for (auto entity : view)
		{
			auto& [mesh, transform] = view.get<MeshComponent<VCGMesh>, TransformComponent>(entity);
			transform.bind();
			PublicSingleton<Renderer>::getInstance().render(mesh.m_Mesh);
		}

		// assimp scene
		auto modelview = m_Registry.view<ModelComponent<AssimpScene>, TransformComponent>();
		for (auto entity : modelview)
		{
			auto& [model, transform] = modelview.get<ModelComponent<AssimpScene>, TransformComponent>(entity);
			transform.bind();
			for (size_t i = 0; i < model.getModel()->m_Meshs.size(); i++)
			{
				auto mesh = model.getModel()->m_Meshs[i];
				if (mesh->m_Texture != nullptr)
				{
					mesh->m_Texture->bind(0);
				}
				else
				{
					PublicSingleton<TexturePool>::getInstance().getTexture("whiteTexture")->bind(0);
				}
				PublicSingleton<Renderer>::getInstance().render(mesh.get());
			}
		}
		PublicSingleton<ParticleSystem>::getInstance().rendertick();
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
