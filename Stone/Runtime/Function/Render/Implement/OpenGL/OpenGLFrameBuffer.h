#pragma once
#include "Function/Render/Interface/FrameBuffer.h"
namespace Stone
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& spec);

        ~OpenGLFrameBuffer();

        void bind() override;
        void unbind() override;
        void resize(uint32_t width, uint32_t height) override;
        uint32_t getColorAttachmentRendererID(uint32_t index = 0) const override;
        virtual int readPixel(uint32_t attachmentIndex, int x, int y) override;
        const FrameBufferSpecification& getSpec() const override { return m_Specification;}
    private:
        uint32_t m_RendererID = 0;
        FrameBufferSpecification m_Specification;
        void invalidate();

        std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentSpecification = FrameBufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
    };
}
