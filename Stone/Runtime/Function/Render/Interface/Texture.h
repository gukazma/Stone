#pragma once
#include<string>
#include<memory>
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
}