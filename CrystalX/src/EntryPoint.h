#pragma once
//WINDOWS_PLATFORM
#ifdef CRYSTALX_WINDOWS
namespace CrystalX
{
	extern Application* Create_Application();
}

//todo: Initfunc

int main(int argc, char** argv)
{
	CrystalX::Log::Initialize();
	CrystalX::Log::EnableFileLogging("test.log", true);
	
	auto app = CrystalX::Create_Application();
	app->Run();
	delete app;
}

#endif
