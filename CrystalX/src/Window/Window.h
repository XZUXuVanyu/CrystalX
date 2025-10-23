#pragma once

#include "Core.h"
#include "Log/Log.h"
#include "Event/Event.h"

namespace CrystalX
{
	struct WindowProperty
	{
		std::string Title;
		std::pair<unsigned int, unsigned int> Size;
		bool Vsync;

		WindowProperty(const std::string& title = "Crystal Engine",
			std::pair<unsigned int, unsigned int> size = std::pair(1280, 720), bool vsync = true)
			: Title(title), Size(size), Vsync(vsync) {
		}
	};

	class CRYSTALX_API Window
	{
	public:

		using WindowEventCallback = std::function<void(Event&)>;
		virtual void SetWindowEventCallback(const WindowEventCallback& callback) = 0;

		virtual ~Window() {};
		virtual void OnUpdate() = 0;

		//返回窗口大小参数 | Return Window size
		virtual std::pair<unsigned int, unsigned int> Size() = 0;

		//返回Vsync状态 | Return Vsync state
		virtual bool Vsync() = 0;
		//设置Vsync状态 | Set Vsync state
		virtual bool Vsync(bool setstate) = 0;

		static Window* Create_Window(const WindowProperty& windowprops = WindowProperty());
	};
}