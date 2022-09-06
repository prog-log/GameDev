#pragma once

#include "Window.h"
#include "Renderer.h"
#include "SceneManager.h"

class Application
{
public:
	void Initialize(HINSTANCE hInst);
	void Loop();
	void Terminate();

private:
	// アプリのメインループ
	bool gameLoop();

private:
	Window		window_;
	Renderer	renderer_;
	SceneManager	sceneManager_;
};
