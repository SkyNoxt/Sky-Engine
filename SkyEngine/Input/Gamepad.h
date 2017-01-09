
#pragma once

class Gamepad
{

public:
	const static unsigned int BUTTON_DPAD_UP = 0x00000001;
	const static unsigned int BUTTON_DPAD_DOWN = 0x00000002;
	const static unsigned int BUTTON_DPAD_LEFT = 0x00000004;
	const static unsigned int BUTTON_DPAD_RIGHT = 0x00000008;
	const static unsigned int BUTTON_START = 0x00000010;
	const static unsigned int BUTTON_BACK = 0x00000020;
	const static unsigned int BUTTON_LEFT_THUMB = 0x00000040;
	const static unsigned int BUTTON_RIGHT_THUMB = 0x00000080;
	const static unsigned int BUTTON_LEFT_SHOULDER = 0x00000100;
	const static unsigned int BUTTON_RIGHT_SHOULDER = 0x00000200;
	const static unsigned int BUTTON_PLAY_PAUSE = 0x00000400;
	const static unsigned int BUTTON_CENTER = 0x00000800;
	const static unsigned int BUTTON_A = 0x00001000;
	const static unsigned int BUTTON_B = 0x00002000;
	const static unsigned int BUTTON_X = 0x00004000;
	const static unsigned int BUTTON_Y = 0x00008000;

	struct State
	{
		unsigned int timestamp = 0;
		unsigned int buttons = 0;
		float leftTrigger = 0.0;
		float rightTrigger = 0.0;
		float leftThumbX = 0.0;
		float leftThumbY = 0.0;
		float rightThumbX = 0.0;
		float rightThumbY = 0.0;
	} state;

	//Member functions
	virtual bool isReady() = 0;
	virtual bool poll() = 0;
};
