
#pragma once

#include <windows.h>

class WinAPIWindow
{
  public:
	// Callbacks
	void (*destroy)() = nullptr;

	// Constructor
	WinAPIWindow(const char* windowTitle, unsigned int x = CW_USEDEFAULT, unsigned int y = CW_USEDEFAULT, unsigned int width = CW_USEDEFAULT, unsigned int height = CW_USEDEFAULT);

	// Destructor
	~WinAPIWindow() = default;

	static void loop()
	{
		MSG message;
		while(GetMessage(&message, nullptr, 0, 0) > 0)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

  private:
	static class WindowClass
	{
	  public:
		const char* name = "Sky Engine Window";

		WindowClass()
		{
			windowClass.lpfnWndProc = callback;
			windowClass.lpszClassName = name;
			windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
			windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			windowClass.cbWndExtra = sizeof(WinAPIWindow*);

			RegisterClass(&windowClass);
		}

		~WindowClass()
		{
			UnregisterClass(name, GetModuleHandle(nullptr));
		}

	  private:
		WNDCLASS windowClass = {};

		static LRESULT callback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			WinAPIWindow* window = (WinAPIWindow*)GetWindowLongPtr(handle, 0);
			switch(message)
			{
				case WM_DESTROY:
					if(window->destroy)
						window->destroy();
					break;
			}
			return DefWindowProc(handle, message, wParam, lParam);
		}
	} windowClass;

	const char* title;
	HWND handle;
};
