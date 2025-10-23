#pragma once
#include "Core.h"
#include "Log/Log.h"
#include "Window/Window.h"
#include "Event/WindowEvent.h"
namespace CrystalX
{
	//Window 类在 Windows 操作系统下的实现 | Detailed implementations of CrystalX::Window under Windows OS.
	class Windows_Window : public Window
	{
	public:
		void SetWindowEventCallback(const WindowEventCallback& callback) override;

		Windows_Window(const WindowProperty& windowprops);
		virtual ~Windows_Window();

		void OnUpdate() override; 

		inline std::pair<unsigned int, unsigned int> Size() override
		{
			return m_Data.Size;
		}
		//返回Vsync状态 | Return Vsync state
		bool Vsync() override;
		//设置Vsync状态 | Set Vsync state
		bool Vsync(bool setstate) override;
		

	private:
		virtual void Initialize(const WindowProperty& winprops);
		virtual void ShutDown();

		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			std::pair<unsigned int, unsigned int> Size;
			bool Vsync;

			WindowEventCallback EventCallback;
			WindowData(const std::string& title = "Crystal Engine",
				std::pair<unsigned int, unsigned int> size = std::pair(1280, 720), bool vsync = true)
				: Title(title), Size(size), Vsync(vsync) {
			}
		};
		WindowData m_Data;
	};
}