#pragma once
#include<memory>
#include<vector>
namespace Stone
{
    enum class FrameBufferTextureFormat
    {
        None = 0,
        RGBA8,
        RED_INTEGER,

        DEPTH24STENCIL8,

        Depth = DEPTH24STENCIL8
    };

    struct FrameBufferTextureSpecification
    {
        FrameBufferTextureSpecification() = default;
        FrameBufferTextureSpecification(FrameBufferTextureFormat format)
            :TextureFormat(format)
        {}

        FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
    };

    struct FrameBufferAttachmentSpecification
    {
        FrameBufferAttachmentSpecification() = default;
        FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
            : Attachments(attachments)
        {}

        std::vector<FrameBufferTextureSpecification> Attachments;
    };

    struct FrameBufferSpecification
    {
        uint32_t Width, Height;
        FrameBufferAttachmentSpecification AttachmentsSpecification;
    };
    
    class FrameBuffer
    {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual uint32_t getColorAttachmentRendererID(uint32_t index = 0) const = 0;
        virtual int readPixel(uint32_t attachmentIndex, int x, int y) = 0;
        virtual void resize(uint32_t width, uint32_t height) = 0;
        static std::shared_ptr<FrameBuffer> create(const FrameBufferSpecification& spec);
        virtual const FrameBufferSpecification& getSpec() const = 0;
    };
}