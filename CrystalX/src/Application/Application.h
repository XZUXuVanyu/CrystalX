//utf8
#pragma once
#include "../Core.h"
namespace CrystalX
{
	class CRYSTALX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/// <summary>
	/// 创建 CrystalX::Application 实例的接口, 具体实现应在 CrystalX app 中给出
	/// A port for creating CrystalX::Application, should be implemented in CrystalX application
	/// </summary>
	/// <returns></returns>
	Application* CreateApplication();
}

