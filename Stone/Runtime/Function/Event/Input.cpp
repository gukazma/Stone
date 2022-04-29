#include "Function/Event/Input.h"
#include "Core/Base/macro.h"
namespace Stone
{
	Input::Input()
	{
		keyMap["Left_Mouse_Down"] = KeyCode::Left_Mouse_Down;
		keyMap["Left_Mouse_Release"] = KeyCode::Left_Mouse_Release;
	}
	MousePos::MousePos(float x, float y)
		: x(x), y(y)
	{
	}
	MousePos::~MousePos()
	{
	}

	MouseAngle::MouseAngle(float x, float y)
		: x(x), y(y)
	{
	}
	MouseAngle::~MouseAngle()
	{
	}
}