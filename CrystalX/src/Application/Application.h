#pragma once
#include "Core.h"
#include "Log/Log.h"
#include "Window/Window.h"

#include "Event/WindowEvent.h"

namespace CrystalX
{
	// CrystalX 应用程序抽象基类 | CrystalX Application BaseClass
	class CRYSTALX_API Application
	{
	public:
		/*实用方法 | Functionalities*/
		//-----------------------------------------------------------------------------------------------
		void Run();
		void Close();
		std::pair<unsigned int, std::string> GetIdentifier() const;
		//-----------------------------------------------------------------------------------------------



	public:
		/*构造函数与析构函数 | Constructor and Deconstructor*/
		//-----------------------------------------------------------------------------------------------
		Application(const std::string& name = "CrystalX_Applicaion", bool windowed = true);
		virtual ~Application();
		//-----------------------------------------------------------------------------------------------



	public:
		/*事件处理 | Process events */
		//-----------------------------------------------------------------------------------------------
		virtual void OnInitialize() {};
		virtual void OnUpdate() {};
		virtual void OnRender() {};
		virtual void OnShutdown() {};

		void OnEvent(Event& event);
		virtual bool OnWindowClose(WindowClose& event);
		Window* GetWindow() const { return m_Window.get(); };

		//-----------------------------------------------------------------------------------------------



	protected:
		/*Application属性 | Status*/
		//-----------------------------------------------------------------------------------------------
		const std::pair<unsigned int, std::string> m_Identifier;
		std::atomic<bool> m_Running{ false };
		std::atomic<bool> m_Windowed{ true };
		//-----------------------------------------------------------------------------------------------

		

	protected:
		/*Application窗口 | Window instance*/
		//-----------------------------------------------------------------------------------------------
		std::unique_ptr<Window> m_Window;
		//-----------------------------------------------------------------------------------------------
		


	private:
		/*用于唯一ID的创建 | For creating unique ID*/
		//-----------------------------------------------------------------------------------------------
		static std::atomic<unsigned int> s_NextId;
		static unsigned int GenerateId();
		//-----------------------------------------------------------------------------------------------
	};



	/// <summary>
	/// 创建 CrystalX::Application 实例的接口, 具体实现应在 CrystalX app 中给出
	/// A port for creating CrystalX::Application, should be implemented in CrystalX application
	/// </summary>
	/// <returns>指向应用实例的指针 | Pointer that points to application instance </returns>
	Application* Create_Application();
}