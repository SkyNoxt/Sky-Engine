
#pragma once

#include <xinput.h>

#include "VirtualGamepad.h"

class WindowsGamepad : public VirtualGamepad
{

public:
	//Constructor
	WindowsGamepad();

	//Member functions
	bool isReady() const override;
	bool poll() override;

	//Destructor
	~WindowsGamepad() override;

private:
	void update(State& dest, const XINPUT_STATE& src);
};
