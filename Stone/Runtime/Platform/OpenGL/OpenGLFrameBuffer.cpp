#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Core/Base/macro.h"
#include <glad/glad.h>
namespace Stone
{
    namespace Utils
    {
        static bool isDepthFormat(FrameBufferTextureFormat format)
        {
            switch (format)
            {
                case FrameBufferTextureFormat::DEPTH24STENCIL8:
                {
                    return true;
                    break;
                }
            }
            return false;
        }

        static void createTextures(uint32_t* outID, uint32_t count)
        {
            glGenTextures(count, outID);
        }
        static void createRenderbuffers(uint32_t* outID, uint32_t count)
        {
            glGenRenderbuffers(count, outID);
        }

        static void bindTexture(uint32_t id)
        {
            glBindTexture(GL_TEXTURE_2D, id);
        }
        static void bindRBO(uint32_t id)
        {
            glBindRenderbuffer(GL_RENDERBUFFER, id);
        }
        static void attachColorTexture(uint32_t id, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, id, 0);
        }
        static void attachDepthTexture(uint32_t id, GLenum format, uint32_t width, uint32_t height)
        {
            glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id);
        }
    }
    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec )
        : m_Specification(spec)
    {
        for (auto attach : m_Specification.AttachmentsSpecification.Attachments)
        {
            if (!Utils::isDepthFormat(attach.TextureFormat))
                m_ColorAttachmentSpecifications.emplace_back(attach);
            else
                m_DepthAttachmentSpecification = attach;
        }
        
        invalidate();
    }

    void OpenGLFrameBuffer::invalidate()
    {
        if (m_RendererID){
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
            glDeleteRenderbuffers(1, &m_DepthAttachment);
            m_ColorAttachments.clear();
            m_DepthAttachment = 0;
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        if (m_ColorAttachmentSpecifications.size())
        {
            m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
            Utils::createTextures(m_ColorAttachments.data(), m_ColorAttachments.size());
            for (size_t i = 0; i < m_ColorAttachments.size(); i++)
            {
                Utils::bindTexture(m_ColorAttachments[i]);
                switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
					case FrameBufferTextureFormat::RGBA8:
						Utils::attachColorTexture(m_ColorAttachments[i], GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
						break;
					case FrameBufferTextureFormat::RED_INTEGER:
						Utils::attachColorTexture(m_ColorAttachments[i], GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
						break;
				}
            }
        }
        if (m_DepthAttachmentSpecification.TextureFormat != FrameBufferTextureFormat::None)
        {
            Utils::createRenderbuffers(&m_DepthAttachment, 1);
            Utils::bindRBO(m_DepthAttachment);
            switch (m_DepthAttachmentSpecification.TextureFormat)
            {
            case FrameBufferTextureFormat::DEPTH24STENCIL8:
                {
                    Utils::attachDepthTexture(m_DepthAttachment, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
                    break;
                }
            }
        }

        if (m_ColorAttachments.size() > 1)
		{
			ASSERT(m_ColorAttachments.size() <= 4,"Framebuffer color size less than 4");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}
        
        ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Specification.Width, m_Specification.Height);
    }
    void OpenGLFrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
        glDeleteRenderbuffers(1, &m_DepthAttachment);
    }

    uint32_t OpenGLFrameBuffer::getColorAttachmentRendererID(uint32_t index) const
    {
        // GU_ASSERT(index > m_ColorAttachments.size(), "index is over size of colorattach");
        return m_ColorAttachments[index];
    }

    void OpenGLFrameBuffer::resize(uint32_t width, uint32_t height)
    {
        m_Specification.Width=width;
        m_Specification.Height = height;
        invalidate();
    }
    int OpenGLFrameBuffer::readPixel(uint32_t attachmentIndex, int x, int y)
    {
        ASSERT(attachmentIndex < m_ColorAttachments.size(), "attachmentIndex is greater than size of attachments");

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
    }
}
