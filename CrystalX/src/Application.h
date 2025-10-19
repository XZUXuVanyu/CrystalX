#pragma once
#include "Core.h"
namespace CrystalX
{
	class CRYSTALX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//This should be defined in client program
	Application* CreateApplication();
}

