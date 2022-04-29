#pragma once
#include "Core/Base/PublicSingleton.h"
#include <filesystem>
#include <Function/UI/UIInterface.h>
namespace Stone
{
    struct EngineInitParams
    {
        std::filesystem::path m_root_folder;
        std::filesystem::path m_config_file_path;
    };
    
    class Engine : public PublicSingleton<Engine>
    {
    public:
        void startEngine(int argc, char* argv[]);
        void setupUISurface(UIInterface* pui) { m_UISurface = pui; }

        void logicalTick();
        void renderTick(uint32_t defaultFramebufferid);

        void shutdownEngine();
        void renderInitialize();
        void logicalInitialize();

        float DeltaTime = 0.0f; // seconds
    public:
        bool         m_isRunning = false;
        UIInterface* m_UISurface;
    };
} // namespace Scaor
