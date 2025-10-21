#include <CrystalX.h>
class SandBox : public CrystalX::Application
{
public:
	SandBox() : Application("Sandbox") { }
	//todo ： figureout why this error happening at debug while not happening at release
	void OnInitialize() override {
		CrystalX::Log::GetCoreLogger()->info("[{}]_id:#{} initialized at memory {} successfully"
			,GetIdentifier().second, GetIdentifier().first, fmt::ptr(this));
	};
};



CrystalX::Application* CrystalX::CreateApplication()
{
	return new SandBox();
}


