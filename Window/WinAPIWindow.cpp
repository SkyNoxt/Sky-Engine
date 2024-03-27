
#if defined(WINDOWS)

#include <windows.h>

#include "WinAPIWindow.h"

void WinAPIWindow::loop()
{
	MSG message;
	while(GetMessage(&message, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void WinAPIWindow::quit()
{
	PostQuitMessage(0);
}

WinAPIWindow::WinAPIWindow(const char* title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	: handle(CreateWindow(windowClass.name, title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr))
{
	BITMAPINFO info = {};
	info.bmiHeader.biSize = sizeof(info.bmiHeader);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = -height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 24;

	device = GetDC((HWND)handle);
	context = CreateCompatibleDC((HDC)device);
	SelectObject((HDC)context, CreateDIBSection((HDC)device, &info, DIB_RGB_COLORS, &data, nullptr, 0));

	SetWindowLongPtr((HWND)handle, 0, (LONG_PTR)this);
	ShowWindow((HWND)handle, SW_SHOW);
}

void WinAPIWindow::update()
{
	InvalidateRect((HWND)handle, nullptr, true);
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
				break;
			case WM_ERASEBKGND:
				return (long long)1;
				break;
			case WM_PAINT:
				BitBlt((HDC)window->device, 0, 0, 1280, 720, (HDC)window->context, 0, 0, SRCCOPY);
				break;
		}
		return DefWindowProc(handle, message, wParam, lParam);
	};
	windowClass.lpszClassName = name;
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
