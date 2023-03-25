
#pragma once

#include "VirtualGamepad.h"

class LinuxGamepad : public VirtualGamepad
{

  public:
	// Constructor
	LinuxGamepad();

	// Member function
	void poll() override;

	// Destructor
	~LinuxGamepad() override;

  private:
	static const float AXIS_MAP;

	int stickDeadzone;
	int triggerDeadzone;
	int joyFile;

	static float mapCenteredAxis(short rawValue, int deadi);
	static float mapAxis(short rawValue, int deadi);

	static void updateButtonMask(bool down, unsigned int& currentMask, unsigned int flag);
	static unsigned int linuxButton(unsigned int btn);
};
