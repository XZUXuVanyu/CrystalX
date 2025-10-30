#pragma once
#include "Core.h"
#include "Log/Log.h"
#include "Event/Event.h"

namespace CrystalX
{
	struct WindowProperty
	{
		std::string Title;
		std::pair<int, int> Size;
		bool VsyncState = true;
		WindowProperty(const std::string& title = "CrystalX", 
			std::pair<int, int> size = { 1920,1080 }, bool vsync = true)
			: Title(title), Size(size), VsyncState(vsync) {};
	};

	using WindowCallbackFunction = std::function<void(Event&)>;

	class CRYSTALX_API Window
	{
	public:
		virtual ~Window() = default;

		virtual std::string GetTitle() const = 0;
		virtual std::pair<int, int> GetSize() const = 0;
		virtual bool GetVsyncState() const = 0;

		virtual void OnUpdate() = 0;
		static std::unique_ptr<Window> Create(const WindowProperty& props = WindowProperty());
		virtual void SetWindowCallback(const WindowCallbackFunction& callbackfunction) = 0;
	};
}