#include "Window.h"
#include <tchar.h>

Window::Window()
	: sizeWindow_()
{
	sizeWindow_.cx = 640;
	sizeWindow_.cy = 480;
}

Window::~Window()
{
}

bool Window::Initialize(HINSTANCE hInst)
{
	// ウインドウ クラスの登録
	wc_.style			= CS_HREDRAW | CS_VREDRAW;
	wc_.lpfnWndProc		= (WNDPROC)Window::MainWndProc;
	wc_.cbClsExtra		= 0;
	wc_.cbWndExtra		= 0;
	wc_.hInstance		= hInst;
	wc_.hIcon			= LoadIcon(hInst, IDI_APPLICATION);
	wc_.hCursor			= LoadCursor(hInst, IDC_ARROW);
	wc_.hbrBackground	= GetSysColorBrush(COLOR_WINDOW);
	wc_.lpszMenuName	= nullptr;
	wc_.lpszClassName	= _T("DrawModel");
	if (!RegisterClass(&wc_)) {
		return false;
	}

	// メイン ウインドウ作成
	RECT rect;
	rect.top	= 0;
	rect.left	= 0;
	rect.right	= sizeWindow_.cx;
	rect.bottom	= sizeWindow_.cy;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWindow_ = CreateWindow(wc_.lpszClassName, _T("DrawModel"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left, rect.bottom - rect.top,
			nullptr, nullptr, hInst, nullptr);
	if (hWindow_ == nullptr) {
		return false;
	}

	// ウインドウ表示
	ShowWindow(hWindow_, SW_SHOWNORMAL);
	UpdateWindow(hWindow_);

	return true;
}

bool Window::Terminate()
{
	DestroyWindow(GetWindowHandle());

	// ウインドウ クラスの登録解除
	UnregisterClass(wc_.lpszClassName, wc_.hInstance);
	hWindow_ = nullptr;
	return true;
}

bool Window::MessageLoop()
{
	// Windowsメッセージループ処理
	if (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE)) { 
		TranslateMessage(&msg_); DispatchMessage(&msg_); 
	} 
	// アプリケーションが終わるときにmessageがWM_QUITになる 
	if (msg_.message == WM_QUIT) { 
		return false; 
	}
	return true;
}

/*static*/ LRESULT CALLBACK Window::MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		// アプリ終了
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	// デフォルト処理（必須）
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Window::OnResize(UINT width, UINT height)
{
	sizeWindow_.cx = width;
	sizeWindow_.cy = height;
}
