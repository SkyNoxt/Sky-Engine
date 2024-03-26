
#pragma once

class WinAPIWindow
{
  public:
	// Callback
	void (*destroy)() = nullptr;

	// Constructor
	WinAPIWindow(const char* title, unsigned int x = 0x80000000, unsigned int y = 0x80000000, unsigned int width = 0x80000000, unsigned int height = 0x80000000);

	// Destructor
	~WinAPIWindow() = default;

	// Static member function
	static void loop();

  private:
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

	// Member variable
	void* handle;
};
