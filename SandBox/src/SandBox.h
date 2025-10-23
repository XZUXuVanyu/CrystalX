#include <CrystalX.h>

class SandBox : public CrystalX::Application
{
public:
	SandBox() : Application("SandBox") {};
	~SandBox() { };


	void OnInitialize()		override;
	void OnUpdate()			override;
	void OnRender()			override;
	void OnShutdown()		override;

	bool OnWindowClose(CrystalX::WindowClose& event) override;
};