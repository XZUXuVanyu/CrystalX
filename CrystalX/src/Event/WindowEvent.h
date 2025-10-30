#pragma once
#include "Event/Event.h"
namespace CrystalX
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() { CRYSTALX_LOG_TRACE("window close"); };
		~WindowCloseEvent() {};
		CRYSTALX_EVENT_REGISTER(WindowCloseEvent);
	};
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height) { 
			CRYSTALX_LOG_TRACE("window resize: {},{}",width,height);
			m_NewWindowSize = { width, height };
		};
		~WindowResizeEvent() {};
		CRYSTALX_EVENT_REGISTER(WindowResizeEvent);

		std::pair<int, int> GetNewWindowSize() { return m_NewWindowSize; };
	private:
		std::pair<int, int> m_NewWindowSize;
	};
	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(int focused) { 
			CRYSTALX_LOG_TRACE("window foucus: {}", focused);
			m_focused = focused;
		};
		~WindowFocusEvent() {};
		CRYSTALX_EVENT_REGISTER(WindowFocusEvent);

		int GetFocusState() { return m_focused; };
	private:
		int m_focused;
	};
	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(int xcoord, int ycoord) {
			CRYSTALX_LOG_TRACE("window resize: {},{}", xcoord, ycoord);
			m_NewWindowCoord = { xcoord, ycoord };
		};
		~WindowMoveEvent() {};
		CRYSTALX_EVENT_REGISTER(WindowMoveEvent);

		std::pair<int, int> GetNewWindowCoord() { return m_NewWindowCoord; };
	private:
		std::pair<int, int> m_NewWindowCoord;
	};
}