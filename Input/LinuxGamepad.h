
#pragma once

#include "VirtualGamepad.h"

namespace Sky::Input
{
	class LinuxGamepad : public VirtualGamepad
	{
	  public:
		// Constructor
		LinuxGamepad();

		// Member function
		void update() override;

		// Destructor
		~LinuxGamepad() override;

	  private:
		static const float AXIS_MAP;

		int joyFile;

		short stickDeadzone;
		short triggerDeadzone;

		static float mapCenteredAxis(short raw, short dead);
		static float mapAxis(short raw, short dead);

		static void updateButtonMask(bool down, unsigned int& currentMask, unsigned int flag);
		static unsigned int linuxButton(unsigned int button);
	};
}
