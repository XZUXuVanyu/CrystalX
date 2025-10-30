#include "Windows_Window.h"
namespace CrystalX
{
	bool Windows_Window::glfwInitialized = false;
	std::unique_ptr<Window> Window::Create(const WindowProperty& props)
	{
		#ifdef CRYSTALX_WINDOWS
				return std::make_unique<Windows_Window>(props);
		#else
				return nullptr;
		#endif
	}
	Windows_Window::Windows_Window(const WindowProperty& windowproperty)
	{
		Initialize(windowproperty);
	}
	void Windows_Window::SetWindowCallback(const WindowCallbackFunction& callbackfunction)
	{
		CRYSTALX_LOG_INFO("set windowcallback");
		m_WindowData.windowcallback = callbackfunction;

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			auto* windowdata_p = static_cast<RuntimeWindowData*>(glfwGetWindowUserPointer(window));
			if (windowdata_p and windowdata_p->windowcallback)
			{
				WindowCloseEvent event;
				windowdata_p->windowcallback(event);
			}
			});
		CRYSTALX_LOG_INFO("set windowclose callback success");

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			auto* windowdata_p = static_cast<RuntimeWindowData*>(glfwGetWindowUserPointer(window));
			if (windowdata_p and windowdata_p->windowcallback)
			{
				windowdata_p->Size = { width,height };
				WindowResizeEvent event(windowdata_p->Size.first, windowdata_p->Size.second);
				windowdata_p->windowcallback(event);
			}
			});
		CRYSTALX_LOG_INFO("set windowresize callback success");

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			auto* windowdata_p = static_cast<RuntimeWindowData*>(glfwGetWindowUserPointer(window));
			if (windowdata_p and windowdata_p->windowcallback)
			{
				WindowFocusEvent event(focused);
				windowdata_p->windowcallback(event);
			}
			});
		CRYSTALX_LOG_INFO("set windowfocus callback success");

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos) {
			auto* windowdata_p = static_cast<RuntimeWindowData*>(glfwGetWindowUserPointer(window));
			if (windowdata_p and windowdata_p->windowcallback)
			{
				WindowMoveEvent event(xpos, ypos);
				windowdata_p->windowcallback(event);
			}
			});
		CRYSTALX_LOG_INFO("set windowmove callback success");

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto* windowdata_p = static_cast<RuntimeWindowData*>(glfwGetWindowUserPointer(window));
			if (windowdata_p and windowdata_p->windowcallback)
			{
				KeyCode keycode = CRYSTALX_GET_KEYCODE(key);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressEvent event(keycode,KeyModifier::None);
						windowdata_p->windowcallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleaseEvent event(keycode, KeyModifier::None);
						windowdata_p->windowcallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyRepeatEvent event(keycode, KeyModifier::None);
						windowdata_p->windowcallback(event);
						break;
					}
				}
			}
			});
		CRYSTALX_LOG_INFO("set key callback success");
	}
	void Windows_Window::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	void Windows_Window::Initialize(const WindowProperty& windowproperty)
	{
		if (!glfwInitialized)
		{
			glfwInit();
			m_WindowData.Title = windowproperty.Title;
			m_WindowData.Size = windowproperty.Size;
			m_WindowData.VsyncState = windowproperty.VsyncState;

			m_Window = glfwCreateWindow(m_WindowData.Size.first, m_WindowData.Size.second, m_WindowData.Title.c_str(),
				nullptr, nullptr);

			glfwSetWindowUserPointer(m_Window, &m_WindowData);
			glfwMakeContextCurrent(m_Window);
		}
	}
}
