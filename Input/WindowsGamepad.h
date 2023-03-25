
#pragma once

#include <windows.h>
#include <xinput.h>

#include "VirtualGamepad.h"

class WindowsGamepad : public VirtualGamepad
{

  public:
	// Constructor
	WindowsGamepad();

	// Member function
	void poll() override;

	// Destructor
	~WindowsGamepad() override;

  private:
	void update(State& dest, const XINPUT_STATE& src);
};
