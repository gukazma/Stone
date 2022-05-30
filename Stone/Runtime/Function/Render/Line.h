#pragma once
#include "Core/Base/PublicSingleton.h"
#include "Function/Render/UniformBuffer.h"
namespace Stone
{
	class Line : PublicSingleton<Line>
	{
	public:
		Line();
		void enable();

		void disable();

	private:
		struct UniformBufferData
		{
			int isLine = 1;
		};
		UniformBufferData m_UniformBufferData;
		std::shared_ptr<UniformBuffer> m_UniformBuffer;
	};
}