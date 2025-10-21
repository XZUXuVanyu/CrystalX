#include "Windows_Window.h"
namespace CrystalX
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create_Window(const WindowProperty& windowprops)
	{
		return new Windows_Window(windowprops);
	}

	Windows_Window::Windows_Window(const WindowProperty& windowprops)
	{
		Initialize(windowprops);
	}

	Windows_Window::~Windows_Window()
	{
		ShutDown();
	}

	void Windows_Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Windows_Window::Vsync()
	{
		return m_Data.Vsync;
	}

	bool Windows_Window::Vsync(bool setstate)
	{
		(setstate) ? glfwSwapInterval(1) : glfwSwapInterval(0);
		m_Data.Vsync = setstate;
		return m_Data.Vsync;
	}

	void Windows_Window::Initialize(const WindowProperty& winprops)
	{
		m_Data.Title = winprops.Title;
		m_Data.Size = winprops.Size;

		Log::CoreLogger()->info("Creating window [{}]", m_Data.Title);
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			CRYSTALX_ASSERT_ERR(success, "Can't initialize glfw");
		}
		m_Window = glfwCreateWindow(m_Data.Size.first, m_Data.Size.second, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// 将窗口实例数据关联到GLFW窗口,用于在回调函数中检索 
		// Associates window instance data with GLFW window for retrieval in callbacks
		glfwSetWindowUserPointer(m_Window, &m_Data);
		Vsync(true);
	}

	void Windows_Window::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

}