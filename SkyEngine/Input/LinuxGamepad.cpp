
#if defined(LINUX)

#include <fcntl.h>
#include <unistd.h>

#include <linux/joystick.h>

#include "LinuxGamepad.h"

char joyDevPath[16] = "/dev/input/js0";

LinuxGamepad::LinuxGamepad()
	: stickDeadzone(8000)
	, triggerDeadzone(400)
	, joyFile(open(joyDevPath, O_RDONLY | O_NONBLOCK))
{
}

void LinuxGamepad::poll()
{
	struct js_event evBuf[255];
	int evCount = read(joyFile, evBuf, sizeof(evBuf));

	evCount /= sizeof(js_event);

	for(int i = 0; i < evCount; ++i)
		{
			const struct js_event& ev = evBuf[i];

			if(ev.type & JS_EVENT_AXIS)
				switch(ev.number)
					{
						case 0:
							state.leftThumbX = mapCenteredAxis(ev.value, stickDeadzone);
							break;
						case 1:
							state.leftThumbY = mapCenteredAxis(ev.value, stickDeadzone);
							break;
						case 2:
							state.leftTrigger = mapAxis(ev.value, triggerDeadzone);
							break;
						case 3:
							state.rightThumbX = mapCenteredAxis(ev.value, stickDeadzone);
							break;
						case 4:
							state.rightThumbY = mapCenteredAxis(ev.value, stickDeadzone);
							break;
						case 5:
							state.rightTrigger = mapAxis(ev.value, triggerDeadzone);
							break;
						case 6:
							if(ev.value < -0.5)
								state.buttons = (state.buttons & (~LinuxGamepad::BUTTON_DPAD_RIGHT)) | LinuxGamepad::BUTTON_DPAD_LEFT;
							else if(ev.value > 0.5)
								state.buttons = (state.buttons & (~LinuxGamepad::BUTTON_DPAD_LEFT)) | LinuxGamepad::BUTTON_DPAD_RIGHT;
							else
								state.buttons &= ~(LinuxGamepad::BUTTON_DPAD_LEFT | LinuxGamepad::BUTTON_DPAD_RIGHT);
							break;
						case 7:
							if(ev.value < -0.5)
								state.buttons = (state.buttons & (~LinuxGamepad::BUTTON_DPAD_DOWN)) | LinuxGamepad::BUTTON_DPAD_UP;
							else if(ev.value > 0.5)
								state.buttons = (state.buttons & (~LinuxGamepad::BUTTON_DPAD_UP)) | LinuxGamepad::BUTTON_DPAD_DOWN;
							else
								state.buttons &= ~(LinuxGamepad::BUTTON_DPAD_DOWN | LinuxGamepad::BUTTON_DPAD_UP);
							break;
					}
		}
}

LinuxGamepad::~LinuxGamepad()
{
	if(joyFile >= 0)
		close(joyFile);
	joyFile = -1;
}

const float LinuxGamepad::AXIS_MAP = 1.0 / 32767.0;

float LinuxGamepad::mapCenteredAxis(short rawValue, int deadi)
{
	const float value = (rawValue * AXIS_MAP);
	const float deadZone = (deadi * AXIS_MAP);
	if(value > deadZone)
		return (value - deadZone) / (1.0f - deadZone);
	if(value < -deadZone)
		return (value + deadZone) / (1.0f - deadZone);
	return 0.0f;
}

float LinuxGamepad::mapAxis(short rawValue, int deadi)
{
	const float value = (rawValue * AXIS_MAP);
	const float deadZone = (deadi * AXIS_MAP);
	if(value > deadZone)
		return (value - deadZone) / (1.0f - deadZone);
	return 0.0f;
}

bool LinuxGamepad::updateButtonMask(bool down, unsigned int& currentMask, unsigned int flag)
{
	if(flag == 0)
		return false;

	unsigned int oldMask = currentMask;
	if(down)
		currentMask |= flag;
	else
		currentMask &= (~flag);

	return oldMask != currentMask;
}

unsigned int LinuxGamepad::linuxButton(unsigned int btn)
{
	switch(btn)
		{
			case 0:
				return BUTTON_A;
			case 1:
				return BUTTON_B;
			case 2:
				return BUTTON_X;
			case 3:
				return BUTTON_Y;
			case 4:
				return BUTTON_LEFT_SHOULDER;
			case 5:
				return BUTTON_RIGHT_SHOULDER;
			case 6:
				return BUTTON_BACK;
			case 7:
				return BUTTON_START;
			case 8:
				return BUTTON_CENTER;
			case 9:
				return BUTTON_LEFT_THUMB;
			case 10:
				return BUTTON_RIGHT_THUMB;
			default:
				return 0;
		}
};

#endif
