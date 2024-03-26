
#if defined(WINDOWS)

#include <windows.h>

#include "WinAPIWindow.h"

WinAPIWindow::WinAPIWindow(const char* title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	: handle(CreateWindow(windowClass.name, title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr))
{
	SetWindowLongPtr((HWND)handle, 0, (LONG_PTR)this);
	ShowWindow((HWND)handle, SW_SHOW);
}

void WinAPIWindow::loop()
{
	MSG message;
	while(GetMessage(&message, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

WinAPIWindow::Class::Class()
{
	WNDCLASS windowClass = {};

	windowClass.lpfnWndProc = [](HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		WinAPIWindow* window = (WinAPIWindow*)GetWindowLongPtr(handle, 0);
		switch(message)
		{
			case WM_DESTROY:
				if(window->destroy)
					window->destroy();
				PostQuitMessage(0);
				break;
		}
		return DefWindowProc(handle, message, wParam, lParam);
	};
	windowClass.lpszClassName = name;
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.cbWndExtra = sizeof(WinAPIWindow*);

	RegisterClass(&windowClass);
}

WinAPIWindow::Class::~Class()
{
	UnregisterClass(name, GetModuleHandle(nullptr));
}

const char* WinAPIWindow::Class::name = "Sky Engine Window";

WinAPIWindow::Class WinAPIWindow::windowClass;

#endif
