#include "Application.h"

namespace CrystalX
{
	/*构造ID | ID Construction*/
	//----------------------------------------------------------------------------------------------
	std::atomic<unsigned int> Application::s_NextId{ 1 };
	unsigned int Application::GenerateId()
	{
		return s_NextId++;
	}
	//----------------------------------------------------------------------------------------------



	/*构造函数与析构函数实现 | Constructor and destructor implementations*/
	//----------------------------------------------------------------------------------------------
	Application::Application(const std::string& name, bool windowed)
		: m_Identifier(GenerateId(), name), m_Windowed(windowed)
	{
		CRYSTALX_trace("on creating at (location = {})", fmt::ptr(this));
		CrystalX::WindowProperty winprops;
		winprops.Title = name;
		m_Window = (m_Windowed) ? std::unique_ptr<Window>(Window::Create_Window(winprops)) : nullptr;
		if (m_Window)
		{
			CRYSTALX_trace("has successfully created window, now setting WindowEventCallback");
			m_Window->SetWindowEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
			CRYSTALX_info("set WindowEventCallback successfully");
		}
		//here should call Application::OnInitialize()
		OnInitialize();
	}
	Application::~Application()
	{
	}
	//----------------------------------------------------------------------------------------------



	/*事件处理 | Process events */
	//-----------------------------------------------------------------------------------------------
	void Application::OnEvent(Event& event)
	{
		CRYSTALX_trace("triggered");
		EventDispatcher Dispatcher(event);

		Dispatcher.Dispatch<WindowClose>([this](WindowClose& e) {
			CRYSTALX_trace("triggered");
			return OnWindowClose(e);
			});
	}

	bool Application::OnWindowClose(WindowClose& event)
	{
		CRYSTALX_trace("triggered");
		Close();
		event.m_EventHandled = true;
		return true;
	}
	//-----------------------------------------------------------------------------------------------


	/*实用方法 | Functionalities*/
	//----------------------------------------------------------------------------------------------
	void Application::Run()
	{
		//here call Application::SandBox::OnInitialize() (override version)
		OnInitialize();
		CRYSTALX_info("now running");

		//主循环 | Main loop
		m_Running = true;
		while (m_Running)
		{
			m_Window->OnUpdate();
			this->OnUpdate();
		}
	}
	void Application::Close()
	{
		OnShutdown();
		m_Running = false;
	}
	std::pair<unsigned int, std::string> Application::GetIdentifier() const
	{
		return m_Identifier;
	}
	//----------------------------------------------------------------------------------------------
}