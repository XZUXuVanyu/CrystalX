#pragma once
#include "Core.h"
#include "Log/Log.h"
#include "Window/Window.h"

namespace CrystalX
{
	//==================================================================================================
	/*
	主要设计思想:
	我希望 CrystalX 作为引擎具有足够的灵活性,它应该只承担基本的数据转译工作(同时保持这些步骤高效),我希望把
	具体的实现更多地放在每个具体工程中完成. 所以这里采用模板模式的设计, CrystalX::Application 将会作为所有
	具体实现的父类,提供必要的及泛用的功能.
	Main design:
	I hope that CrystalX, as an engine, has enough flexibility. It should only handle the basic
	data translation tasks (while keeping them efficient). I want the detailed implementations
	to be mainly completed in each individual project. Therefore, the template pattern is used here,
	with CrystalX::Application serving as the parent class for all specific implementations,
	providing the necessary and general-purpose functions.
	*/
	//==================================================================================================
	// CrystalX 应用程序抽象基类 | CrystalX Application BaseClass
	class CRYSTALX_API Application
	{
	public:
		//----------------------------------------------------------------------------------------------
		// 构造函数与析构函数 | Constructors and Destructor
		//----------------------------------------------------------------------------------------------
		/// <summary>
		/// Application 构造函数,要求提供应用名称
		/// Application constructor, requires application name
		/// </summary>
		/// <param name="name">应用名称 | Application name</param>
		/// <param name="windowed">是否为应用创建窗口 | If this application needs a window</param>
		Application(const std::string& name = "CrystalX_Applicaion", bool windowed = true);

		virtual ~Application();

		//----------------------------------------------------------------------------------------------
		// 基类须提供的基本控制功能 | Basic functions that should be provided by base class
		//----------------------------------------------------------------------------------------------
		/// 启动应用主循环 | Start application main loop
		void Run();

		/// 请求关闭应用 | Request application to close
		void RequestClose();

		/// <summary>
		/// 获取应用唯一标识符 | Get application unique identifier
		/// </summary>
		/// <returns>标识符对 (ID, 名称) | Identifier pair (ID, name)</returns>
		std::pair<unsigned int, std::string> GetIdentifier() const;

		/// 应用初始化回调 | Application initialization callback
		virtual void OnInitialize() {
			Log::CoreLogger()->info("[{}](id = {}) on initialize (by defalut CrystalX::Application Oninitialize() ) at memory {}"
				,m_Identifier.second, m_Identifier.first, fmt::ptr(this));
		};

		/// 应用更新回调 | Application update callback
		virtual void OnUpdate() {};

		/// 应用渲染回调 | Application render callback
		virtual void OnRender() {};

		/// 应用关闭回调 | Application shutdown callback
		virtual void OnShutdown() {};

	protected:
		// 应用运行状态 | Application running state
		std::atomic<bool> m_Running{ false };
		
		// 应用的唯一标识符 | Application 's unique identifier
		const std::pair<unsigned int, std::string> m_Identifier;

		//是否为窗口应用程序 | If application needs a window
		std::atomic<bool> m_Windowed{ true };
		std::unique_ptr<Window> m_Window;

	private:
		// 下一个可用的应用ID | Next available application ID
		static std::atomic<unsigned int> s_NextId;

		/// <summary>
		/// 生成唯一应用ID | Generate unique application ID
		/// </summary>
		/// <returns>唯一ID | Unique ID</returns>
		static unsigned int GenerateId();
	};

	/// <summary>
	/// 创建 CrystalX::Application 实例的接口, 具体实现应在 CrystalX app 中给出
	/// A port for creating CrystalX::Application, should be implemented in CrystalX application
	/// </summary>
	/// <returns>指向应用实例的指针 | Pointer that points to application instance </returns>
	Application* Create_Application();
}