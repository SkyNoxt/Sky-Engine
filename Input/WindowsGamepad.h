
#pragma once

#include "VirtualGamepad.h"

namespace Sky::Input
{
	class WindowsGamepad : public VirtualGamepad
	{
	  public:
		// Constructor
		WindowsGamepad();

		// Member function
		void update() override;

		// Destructor
		~WindowsGamepad() override;
	};
}
