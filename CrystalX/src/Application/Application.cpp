#include "Application.h"
namespace CrystalX
{
	std::atomic<unsigned int> Application::s_NextId = { 1 };

	void Application::Run()
	{
		UserInitialize();
		m_Running = true;
		while (m_Running)
		{
			UserUpdate();
			if (m_Windowed && m_Window)
			{
				m_Window->OnUpdate();
			}
		}
		
	}

	void Application::ShutDown()
	{
		m_Running = false;
	}

	std::pair<unsigned int, std::string> Application::GetIdentifier() const
	{
		return m_Identifier;
	}

	void Application::PatchEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		CRYSTALX_EVENT_DISPATCH(dispatcher, WindowCloseEvent, UserOnWindowClose);
		CRYSTALX_EVENT_DISPATCH(dispatcher, WindowResizeEvent, UserOnWindowResize);
		CRYSTALX_EVENT_DISPATCH(dispatcher, WindowFocusEvent, UserOnWindowFocus);
		CRYSTALX_EVENT_DISPATCH(dispatcher, WindowMoveEvent, UserOnWindowMove);
		CRYSTALX_EVENT_DISPATCH(dispatcher, KeyPressEvent, UserOnKeyPress);
		CRYSTALX_EVENT_DISPATCH(dispatcher, KeyReleaseEvent, UserOnKeyRelease);
		CRYSTALX_EVENT_DISPATCH(dispatcher, KeyRepeatEvent, UserOnKeyRepeat);
	}

	Application::Application(const std::string& name, bool windowed)
		: m_Identifier(GenerateId(), name), m_Windowed(windowed)
	{
		CRYSTALX_LOG_TRACE("application create");
		if (m_Windowed)
		{
			WindowProperty windowproperty;
			windowproperty.Title = name;
			m_Window = Window::Create(windowproperty);
			CRYSTALX_LOG_TRACE("window create");
			m_Window->SetWindowCallback(std::bind(&Application::PatchEvent, this, std::placeholders::_1));
		}
	}

	unsigned int Application::GenerateId()
	{
		return s_NextId++;
	}
}