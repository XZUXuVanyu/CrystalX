#include "Event.h"

namespace CrystalX
{
	class WindowClose : public Event
	{
	public:
		WindowClose() { CRYSTALX_trace("event created"); };
		~WindowClose() { CRYSTALX_trace("event destroyed"); };

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(ApplicationEvent);
		
	};
}