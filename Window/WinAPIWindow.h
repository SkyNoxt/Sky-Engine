
#pragma once

class WinAPIWindow
{
  public:
	// Static member functions
	static void loop();
	static void quit();

	// Callback
	void (*destroy)() = nullptr;

	// Constructor
	WinAPIWindow(const char* title, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	// Member function
	void update();

	// Destructor
	~WinAPIWindow() = default;

	// private:
	static class Class
	{
	  public:
		// Static member variable
		static const char* name;

		// Constructor
		Class();

		// Destructor
		~Class();
	} windowClass;

	// Member variables
	void* handle;

	void* context;
	void* device;
	void* data;
};
