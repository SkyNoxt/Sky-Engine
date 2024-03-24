
#include "WinAPIWindow.h"

WinAPIWindow::WindowClass WinAPIWindow::windowClass;

WinAPIWindow::WinAPIWindow(const char* windowTitle, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	: title(windowTitle)
	, handle(CreateWindow(windowClass.name, title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr))
{
	SetWindowLongPtr(handle, 0, (LONG_PTR)this);
	ShowWindow(handle, SW_SHOW);
}
