#pragma once
#include "Core.h"
#include "Log/Log.h"
#include "Window/Window.h"
#include "Event/WindowEvent.h"
#include "Event/KeyEvent.h"
namespace CrystalX
{
	class CRYSTALX_API Application
	{
	public:
		Application(const std::string& name = "CrystalX_Applicaion", bool windowed = true);
		virtual ~Application() = default;

	public:
		//various event callback
		//===========================================================================================================
		void PatchEvent(Event& event);
		virtual void UserOnWindowClose(WindowCloseEvent& event) {
			CRYSTALX_LOG_INFO("window close");
			ShutDown();
		};
		virtual void UserOnWindowResize(WindowResizeEvent& event) {
			CRYSTALX_LOG_TRACE("window resize: {},{}",
				event.GetNewWindowSize().first, event.GetNewWindowSize().first);
		};
		virtual void UserOnWindowFocus(WindowFocusEvent& event) {
			CRYSTALX_LOG_INFO("window focus: {}", (event.GetFocusState()) ? "true" : "false");
		};
		virtual void UserOnWindowMove(WindowMoveEvent& event) {
			CRYSTALX_LOG_TRACE("window moved to: {},{}",
				event.GetNewWindowCoord().first, event.GetNewWindowCoord().second);
		};
		virtual void UserOnKeyPress(KeyPressEvent& event) {
			CRYSTALX_LOG_INFO("{} press",static_cast<int>(event.GetKeyCode()));
		};
		virtual void UserOnKeyRelease(KeyReleaseEvent& event) {
			CRYSTALX_LOG_INFO("{} release", static_cast<int>(event.GetKeyCode()));
		};
		virtual void UserOnKeyRepeat(KeyRepeatEvent& event) {
			CRYSTALX_LOG_INFO("{} repeat", static_cast<int>(event.GetKeyCode()));
		};
		//===========================================================================================================


	public:
		virtual void UserInitialize() {};
		virtual void UserUpdate() {};
		virtual void UserRender() {};
		virtual void UserShutdown() {};

	public:
		void Run();
		void ShutDown();
		std::pair<unsigned int, std::string> GetIdentifier() const;
		Window* GetWindow() const { return m_Window.get(); };

	protected:
		const std::pair<unsigned int, std::string> m_Identifier;
		std::atomic<bool> m_Running{ false };
		std::atomic<bool> m_Windowed{ true };

	protected:
		std::unique_ptr<Window> m_Window;
		
	private:
		static std::atomic<unsigned int> s_NextId;
		static unsigned int GenerateId();
	};

	Application* Create_Application();
}