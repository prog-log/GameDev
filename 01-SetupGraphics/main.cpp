#include <Windows.h>
#include "Application.h"

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	Application* application = new Application();

	application->Initialize(hInst);

	application->Loop();

	application->Terminate();

	delete(application);

	return 0;
}
