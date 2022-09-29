#pragma once
#include <windows.h>

class Window
{
public:
	Window();
	virtual ~Window();

	bool Initialize(HINSTANCE hInst);

	bool Terminate();

	bool MessageLoop();

	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void OnResize(UINT width, UINT height);

	HWND	GetWindowHandle() { return hWindow_; }

private:
	WNDCLASS	wc_;
	HWND		hWindow_ = nullptr;
	SIZE		sizeWindow_;
	MSG			msg_ = {};
};
