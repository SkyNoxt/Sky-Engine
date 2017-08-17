
#pragma once

#include "Gamepad.h"

class LinuxGamepad : public Gamepad
{

public:
	//Constructor
	LinuxGamepad();

	//Member functions
	bool isReady();
	bool poll();

	//Destructor
	~LinuxGamepad();

private:
	static const float AXIS_MAP;

	int stickDeadzone;
	int triggerDeadzone;
	int joyFile;

	static float mapCenteredAxis(int valueS16, int deadi);
	static float mapAxis(int valueS16, int deadi);

	static bool updateButtonMask(bool down, unsigned int& currentMask, unsigned int flag);
	static unsigned int linuxButton(unsigned int btn);
};
