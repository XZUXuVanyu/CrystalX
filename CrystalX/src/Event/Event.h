#pragma once
#include "Core.h"
namespace CrystalX
{
	/*EventType 定义 CrystalX 的统一事件类型  | EventType defines unified event type for CrystalX*/
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMove,
		KeyPress, KeyRelease, KeyRepeat,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	};


	/*EventCategory 用于事件快速分类  | EventCategory is used for categorize events*/
	enum EventCategory {
		None = 0,
		ApplicationEvent		= BIT_MASK(0),
		InputEvent				= BIT_MASK(1),
		KeyboardPressEvent		= BIT_MASK(2),
		MouseMoveEvent			= BIT_MASK(3),
		MousePressCategory		= BIT_MASK(4)
	};
}

namespace CrystalX
{
	/*CrystalX 事件基类 | CrystalX base event class*/
	class CRYSTALX_API Event {
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType()		const = 0;
		virtual const char* GetEventName()		const = 0;
		virtual int GetCategoryFlags()			const = 0;

		bool IsInCategory(EventCategory category) const 
		{
			return GetCategoryFlags() & category;
		}
		bool m_EventHandled = false;
	};


	//todo: add descriptions here

	/*CrystalX 事件分发器 | CrystalX event dispatcher*/
	class EventDispatcher {
	public:
		/*构造函数 | Constructor*/
		//----------------------------------------------------------------------------------------------
		EventDispatcher(Event& event) : m_Event(event) 
		{
			CRYSTALX_trace("event dispatcher created");
		}
		~EventDispatcher()
		{
			CRYSTALX_trace("event dispatcher destroyed");
		}
		//----------------------------------------------------------------------------------------------

		

	public:
		/*编译期类型检查 | Compiletime event type check*/
		//----------------------------------------------------------------------------------------------
		template<typename Event_Type, typename Function_Type>
		bool Dispatch(const Function_Type& func)
		{
			if (m_Event.GetEventType() == Event_Type::StaticGetEventType())
			{
				CRYSTALX_trace("triggered");
				m_Event.m_EventHandled = func(static_cast<Event_Type&>(m_Event));
				CRYSTALX_trace("event handled");
				return true;
			}
			return false;
		}
		//----------------------------------------------------------------------------------------------



	private:
		Event& m_Event;
	};



#define EVENT_CLASS_TYPE(type) \
static EventType StaticGetEventType() { return EventType::type; }\
virtual EventType GetEventType() const override { return StaticGetEventType(); }\
virtual const char* GetEventName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

}