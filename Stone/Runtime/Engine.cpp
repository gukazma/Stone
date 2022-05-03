#include "Engine.h"

#include "Function/Render/Interface/Renderer.h"
#include "Function/Event/EventSystem.h"

#include "Function/Scene/EditCamera.h"
#include "Function/Scene/Scene.h"

#include "Function/Render/Interface/Renderer.h"
#include "Function/Render/Interface/Texture.h"
#include "Function/Render/Interface/Shader.h"

#include "Resource/Data/Implement/VCG/VCGMesh.h"

#include "Core/Base/macro.h"
#include <thread>
#include <glad/glad.h>
namespace Stone
{
    VCGMesh* vcgmesh;
    std::shared_ptr<Texture2D> _texture;
    void Engine::startEngine(int argc, char* argv[])
    {
        LOG_INFO("Start editor engine");
        m_isRunning = true;
    }
    void Engine::logicalTick()
    {
        PublicSingleton<EventSystem>::getInstance().processEvents();
        m_UISurface->tick();
    }
    void Engine::renderTick(uint32_t defaultFramebufferid)
    { 
        PublicSingleton<Renderer>::getInstance().begin();
        PublicSingleton<Scene>::getInstance().renderTick();
        //_texture->bind(0);
        //PublicSingleton<Renderer>::getInstance().render(vcgmesh);

        PublicSingleton<Renderer>::getInstance().end(defaultFramebufferid);
    }

    void Engine::renderInitialize()
    {
        PublicSingleton<Renderer>::getInstance().initialize();
        PublicSingleton<Scene>::getInstance().initialize();
        //_texture = Texture2D::create("D:/datas/ply/tayv6_2K_Albedo.png");
    }
    void Engine::logicalInitialize()
    {
    }

    void Engine::shutdownEngine()
    {
        LOG_INFO("Shutdown editor engine");

        // Shut down event system
        PublicSingleton<EventSystem>::getInstance().unregisterAll(&PublicSingleton<EditorCamera>::getInstance());
        PublicSingleton<EventSystem>::getInstance().shutdown();

        // waiting for other thread to release
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        m_isRunning = false;
    }
    
} // namespace SoaScape
