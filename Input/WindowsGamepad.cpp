
#if defined(WINDOWS)

#include <cmath>

#include <windows.h>
#include <xinput.h>

#include "WindowsGamepad.h"

using Sky::Input::WindowsGamepad;

WindowsGamepad::WindowsGamepad()
{
}

void WindowsGamepad::update()
{
	XINPUT_STATE newState;
	XInputGetState(0, &newState);

	float lx = newState.Gamepad.sThumbLX;
	float ly = newState.Gamepad.sThumbLY;
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

	float rx = newState.Gamepad.sThumbRX;
	float ry = newState.Gamepad.sThumbRY;
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
	if(newState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		lt = float(newState.Gamepad.bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

	float rt = 0.0f;
	if(newState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		rt = float(newState.Gamepad.bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

	state.buttons = newState.Gamepad.wButtons;
	state.leftThumbX = lx;
	state.leftThumbY = -ly; // flip to match Android
	state.rightThumbX = rx;
	state.rightThumbY = -ry; // flip to match Android
	state.leftTrigger = lt;
	state.rightTrigger = rt;
}

WindowsGamepad::~WindowsGamepad()
{
}

#endif
