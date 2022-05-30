#pragma once
#include<memory>
namespace Stone
{
    class UniformBuffer
    {
    public:
        virtual ~UniformBuffer() = default;
        virtual void setData(const void* data, uint32_t size, uint32_t offset = 0) = 0;
        virtual void bind(uint32_t binding = 0) = 0;
        virtual void unbind() = 0;
        static std::shared_ptr<UniformBuffer> create(uint32_t size = 152);
    };
}