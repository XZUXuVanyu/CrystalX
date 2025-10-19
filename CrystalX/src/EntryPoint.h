#pragma once

#ifdef CRYSTALX_WINDOWS

namespace CrystalX
{
	extern Application* CreateApplication();
}


int main(int argc, char** argv)
{
	printf("CrystalX Running.\n");
	auto app = CrystalX::CreateApplication();
	app->Run();
	delete app;
}

#endif // 
