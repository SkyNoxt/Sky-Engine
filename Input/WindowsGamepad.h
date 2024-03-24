
#pragma once

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
};
