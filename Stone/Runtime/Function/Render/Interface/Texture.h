#pragma once
#include <string>
#include <memory>
#include <map>
#include <Core/Base/PublicSingleton.h>
namespace Stone
{
    class Texture
    {
    public:
        virtual ~Texture() = default;
        virtual void bind(uint32_t slot) = 0;
        virtual void setData(void* data, uint32_t size) = 0;
        virtual uint32_t getRendererID() = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> create(uint32_t width, uint32_t height);
        static std::shared_ptr<Texture2D> create(const std::string& path);
    };

    class TexturePool : public PublicSingleton<TexturePool>
    {
    public:
        std::shared_ptr<Texture2D> getTexture(const std::string& path)
        {
            if (m_Map.find(path)==m_Map.end())
            {
                m_Map[path] = Texture2D::create(path);
            }
            return m_Map[path];
        }
    private:
        std::map <std::string, std::shared_ptr<Texture2D>> m_Map;
    };
}