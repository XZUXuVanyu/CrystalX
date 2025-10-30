#pragma once
#include "Window/Window.h"
#include "Event/WindowEvent.h"
#include "Event/KeyEvent.h"
#include "Window/Platform/KeyMapper.h"
namespace CrystalX
{
	
	class Windows_Window : public Window
	{
	public:
		Windows_Window(const WindowProperty& windowproperty);
		virtual void SetWindowCallback(const WindowCallbackFunction& callbackfunction) override;
		virtual void OnUpdate() override;

		virtual std::string GetTitle() const override { return m_WindowData.Title; }
		virtual std::pair<int, int> GetSize() const override { return m_WindowData.Size; }
		virtual bool GetVsyncState() const override { return m_WindowData.VsyncState; }

	private:
		void Initialize(const WindowProperty& windowproperty);
		struct RuntimeWindowData
		{
			std::string Title;
			std::pair<int, int> Size;
			bool VsyncState = true;

			WindowCallbackFunction windowcallback;

			RuntimeWindowData(const std::string& title = "CrystalX",
				std::pair<int, int> size = { 1920,1080 }, bool vsync = true)
				: Title(title), Size(size), VsyncState(vsync) {
			};
		};
		GLFWwindow* m_Window;
		RuntimeWindowData m_WindowData;
		static bool glfwInitialized;
	};
}