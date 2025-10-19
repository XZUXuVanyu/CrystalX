#pragma once
#include <string>
#include <functional>
namespace CrystalX
{
	enum class EventType
	{
		None = 0x00,
		WindowClose = 0x01, WindowResize = 0x02, WindowFoucus = 0x03, WindowLostFocus = 0x04, WindowMoved = 0x05,
		AppTick = 0x06, AppUpdate = 0x07, AppRender = 0x08,
		KeyPress = 0x09, KeyRelease = 0x0A,
		MouseButtonPress = 0x0B, MouseButtonRelease = 0x0C, MouseMove = 0x0D, MouseScroll = 0x0E
	};

	enum EventCategory
	{
		None = 0,
		Event_Application = 1,
		Event_Input = 2,
		Event_KeyBoard = 3,
		Event_MouseMove = 4,
		Event_MousePress = 5,
	};

	class Event
	{
	public:
		Event();
	};

}

