#pragma once
#include "Core.h"
#include "Log/Log.h"

namespace CrystalX
{
	enum class EventType
	{
		None = 0,
		WindowCloseEvent, WindowResizeEvent, WindowFocusEvent, WindowMoveEvent,
		KeyPressEvent, KeyReleaseEvent, KeyRepeatEvent,
		MouseButtonPressEvent, MouseButtonReleaseEvent, MouseMoveEvent, MouseScrollEvent
	};

	class CRYSTALX_API Event
	{
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;
		bool m_EventHandled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) {};
		template<typename TypeToCheck, typename FunctionType>
		bool Dispatch(const FunctionType& callbackfunction)
		{
			if (m_Event.GetEventType() == TypeToCheck::TypeOf())
			{
				callbackfunction(static_cast<TypeToCheck&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}

#define CRYSTALX_EVENT_REGISTER(type) \
	static CrystalX::EventType TypeOf() { return CrystalX::EventType::type; } \
	virtual CrystalX::EventType GetEventType() const override { return TypeOf(); }

#define CRYSTALX_EVENT_DISPATCH(dispatcher, event, handler) \
dispatcher.Dispatch<event>([this](event& e) { return handler(e); })
