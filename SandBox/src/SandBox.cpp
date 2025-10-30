#include "CrystalX.h"
namespace CrystalX
{
	class SandBox : public CrystalX::Application
	{
	public:
		SandBox() : Application("SandBox") {};
		~SandBox() {};
		void UserOnKeyPress(KeyPressEvent& event) {
			if (event.GetKeyCode() == KeyCode::Escape)
			{
				ShutDown();
			}
		};
	};

	Application* Create_Application()
	{
		return new SandBox();
	}
}