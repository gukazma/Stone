#pragma once
#include <unordered_map>
#include "Core/Base/PublicSingleton.h"
namespace Stone
{
	class MousePos
	{
	public:
		MousePos(float x, float y);
		~MousePos();
		float x;
		float y;
	};
	class MouseAngle
	{
	public:
		MouseAngle(float x, float y);
		~MouseAngle();
		float x;
		float y;
	};


	// TODO: key map
	class Input : public PublicSingleton<Input>
	{
	public:
		Input();
		enum class KeyCode
		{
			Left_Mouse_Down = 0,
			Left_Mouse_Release,
		};
		std::unordered_map<std::string, KeyCode> keyMap;
	};
}