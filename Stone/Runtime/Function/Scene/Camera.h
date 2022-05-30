#pragma once
#include "Function/Render/UniformBuffer.h"
namespace Stone
{
	class Camera
	{
	public:
		Camera() = default;

		virtual ~Camera() = default;
		
		virtual void bind(size_t index = 0) = 0;
	protected:
	};
}