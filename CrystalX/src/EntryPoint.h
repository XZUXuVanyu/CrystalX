#pragma once

//WINDOWS_PLATFORM
#ifdef CRYSTALX_WINDOWS
namespace CrystalX
{
	extern Application* CreateApplication();
}

//todo: Initfunc
int main(int argc, char** argv)
{
	CrystalX::Log::Init();
	CRYSTALX_CORE_WARN("Initialized log!");
	auto app = CrystalX::CreateApplication();
	app->Run();
	delete app;
}

#endif



