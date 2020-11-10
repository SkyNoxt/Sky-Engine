
#if defined(WINDOWS)

#include <cmath>

#include "WindowsGamepad.h"

WindowsGamepad::WindowsGamepad()
{
}

void WindowsGamepad::poll()
{
	XINPUT_STATE newState;
	XInputGetState(0, &newState);

	update(state, newState);
}

void WindowsGamepad::update(State& dest, const XINPUT_STATE& src)
{
	float lx = src.Gamepad.sThumbLX;
	float ly = src.Gamepad.sThumbLY;
	float lMag = std::sqrt(lx * lx + ly * ly);

	if(lMag > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		lx /= lMag;
		ly /= lMag;

		lMag = (lMag - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / float(32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		lx *= lMag;
		ly *= lMag;
	}
	else
	{
		lx = ly = 0.0f;
	}

	float rx = src.Gamepad.sThumbRX;
	float ry = src.Gamepad.sThumbRY;
	float rMag = std::sqrt(rx * rx + ry * ry);

	if(rMag > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		rx /= rMag;
		ry /= rMag;

		rMag = (rMag - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / float(32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

		rx *= rMag;
		ry *= rMag;
	}
	else
	{
		rx = ry = 0.0f;
	}

	float lt = 0.0f;
	if(src.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		lt = float(src.Gamepad.bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

	float rt = 0.0f;
	if(src.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		rt = float(src.Gamepad.bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

	dest.buttons = src.Gamepad.wButtons;
	dest.leftThumbX = lx;
	dest.leftThumbY = -ly; // flip to match Android
	dest.rightThumbX = rx;
	dest.rightThumbY = -ry; // flip to match Android
	dest.leftTrigger = lt;
	dest.rightTrigger = rt;
}

WindowsGamepad::~WindowsGamepad()
{
}

#endif