
#pragma once

#include "Gamepad.h"

class LinuxGamepad : public Gamepad
{

public:
	//Constructor
	LinuxGamepad();

	//Member functions
	virtual bool isReady();
	virtual bool poll();

	//Destructor
	virtual ~LinuxGamepad();

private:
	static const float AXIS_MAP;

	int joyFile;
	int stickDeadzone;
	int triggerDeadzone;

	float mapCenteredAxis(int valueS16, int deadi);
	float mapAxis(int valueS16, int deadi);

	bool updateButtonMask(bool down, unsigned int& currentMask, unsigned int flag);
	unsigned int linuxButton(unsigned int btn);
};
