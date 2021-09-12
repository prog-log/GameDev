#include "Application.h"

void Application::Initialize(HINSTANCE hInst)
{
	window_.Initialize(hInst);
}

void Application::Loop()
{
	while (true) {
		bool result = window_.MessageLoop();
		if (result == false) break;

		result = gameLoop();
		if (result == false) break;
	}
}

void Application::Terminate()
{
	window_.Terminate();
}

bool Application::gameLoop()
{
	return true;
}

