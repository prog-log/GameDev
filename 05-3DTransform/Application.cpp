#include "Application.h"

void Application::Initialize(HINSTANCE hInst)
{
	window_.Initialize(hInst);
	renderer_.Initialize(window_.GetWindowHandle());
	sceneManager_.Initialize(renderer_);
}

void Application::Loop()
{
	while (true) {
		bool result = window_.MessageLoop();
		if (result == false) break;

		bool ret = gameLoop();
		if (ret == false) break;
	}
}

void Application::Terminate()
{
	sceneManager_.Terminate();
	renderer_.Terminate();
	window_.Terminate();
}

bool Application::gameLoop()
{
	sceneManager_.Update();

	renderer_.Draw();

	sceneManager_.Draw();

	renderer_.Swap();

	Sleep(10);

	return true;
}

