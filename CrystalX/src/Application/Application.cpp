#include "Application.h"

namespace CrystalX
{
	//----------------------------------------------------------------------------------------------
	// 静态成员初始化 | Static member initialization
	//----------------------------------------------------------------------------------------------
	std::atomic<unsigned int> Application::s_NextId{ 1 };

	//----------------------------------------------------------------------------------------------
	// 私有方法实现 | Private method implementations
	//----------------------------------------------------------------------------------------------
	unsigned int Application::GenerateId()
	{
		return s_NextId++;
	}

	//----------------------------------------------------------------------------------------------
	// 构造函数与析构函数实现 | Constructor and destructor implementations
	//----------------------------------------------------------------------------------------------
	Application::Application(const std::string& name)
		: m_Identifier(GenerateId(), name)
	{}

	Application::Application()
		: m_Identifier(GenerateId(), "CrystalX_Application_"+std::to_string(m_Identifier.first))
	{
	}

	Application::~Application()
	{
		// 确保应用已停止运行 | Ensure application has stopped running
		if (m_Running)
		{
			RequestClose();
		}
	}

	//----------------------------------------------------------------------------------------------
	// 公共方法实现 | Public method implementations
	//----------------------------------------------------------------------------------------------
	void Application::Run()
	{
		// 调用应用初始化回调 | Call application initialization callback
		OnInitialize();
		
		Log::GetCoreLogger()->info("[{}]_id:#{} starting main loop",m_Identifier.second, m_Identifier.first);

		// 设置运行状态并进入主循环 | Set running state and enter main loop
		m_Running = true;
		while (m_Running)
		{
			OnUpdate();
			OnRender();
		}

		Log::GetCoreLogger()->warn("Scheduling [{}]_id:#{} shutdown",
			m_Identifier.second, m_Identifier.first);
		OnShutdown();
		Log::GetCoreLogger()->info("Scheduling [{}]_id:#{} shutdown",
			m_Identifier.second, m_Identifier.first);
		
	}

	void Application::RequestClose()
	{
		m_Running = false;
	}

	std::pair<unsigned int, std::string> Application::GetIdentifier() const
	{
		return m_Identifier;
	}
}