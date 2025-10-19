#include <CrystalX.h>

class SandBox : public CrystalX::Application
{
public:
	

private:

};

CrystalX::Application* CrystalX::CreateApplication()
{
	return new SandBox();
}