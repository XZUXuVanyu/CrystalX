#include "SandBox.h"

void SandBox::OnInitialize()
{
	CRYSTALX_trace("initialize sandbox");
}
void SandBox::OnUpdate()
{

}

void SandBox::OnRender()
{

}

void SandBox::OnShutdown()
{
	CRYSTALX_trace("closing sandbox");
}

bool SandBox::OnWindowClose(CrystalX::WindowClose& event)
{
	return CrystalX::Application::OnWindowClose(event);
}

CrystalX::Application* CrystalX::Create_Application()
{
	return new SandBox();
}
