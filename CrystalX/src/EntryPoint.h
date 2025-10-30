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
	CrystalX::Log::SetLogLevel(spdlog::level::debug);
	auto app1 = CrystalX::Create_Application(); 
	app1->Run();
	delete app1;
}
#endif
