#pragma once
#include "Core/Base/macro.h"
namespace Stone
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:    return 0;
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

        BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
            case ShaderDataType::None:    return 0;
			case ShaderDataType::Float:    return 1;
			case ShaderDataType::Float2:   return 2;
			case ShaderDataType::Float3:   return 3;
			case ShaderDataType::Float4:   return 4;
			case ShaderDataType::Mat3:     return 3;
			case ShaderDataType::Mat4:     return 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
            }
        }


    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferElement> elements)
            : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

        const std::vector<BufferElement>& getElements() const { return m_Elements; }
        uint32_t getStride() const { return m_Stride; }
    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
            
        }
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void setData(const void* data, uint32_t size) = 0;
        virtual void setLayout(const BufferLayout& bufferLayout) = 0;
        virtual const BufferLayout& getLayout() const = 0;

        static std::shared_ptr<VertexBuffer> create(const void* data, uint32_t size);
        static std::shared_ptr<VertexBuffer> create(uint32_t size);
    };

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;
		virtual void bind() = 0;
		virtual void unbind() = 0; 
        virtual uint32_t getCount() = 0;

		static std::shared_ptr<IndexBuffer> create(const uint32_t* indices, uint32_t count);
	};
}
