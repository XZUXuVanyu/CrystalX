#include <CrystalX.h>
class SandBox : public CrystalX::Application
{
public:
	SandBox() : Application("Sandbox") { }
	//todo ： figureout why this error happening at debug while not happening at release
	void OnInitialize() override
	{
		CrystalX::Log::CoreLogger()->info("[{}](id = {}) initialized at memory {} successfully"
			,GetIdentifier().second, GetIdentifier().first, fmt::ptr(this));
	};
	void OnUpdate() override
	{
		if (m_Windowed and m_Window)
		{
			m_Window->OnUpdate();
		}
	}
};

CrystalX::Application* CrystalX::Create_Application()
{
	return new SandBox();
}