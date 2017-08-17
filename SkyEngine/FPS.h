
#pragma once

#include <Camera/Camera.h>
#include <Input/Gamepad.h>

class FPS
{

public:
	//Constructor
	FPS(Camera* cam, Gamepad* pad, float moveVel = 1.0, float rotationVel = 1.0);

	//Member function
	void update();

	//Destructor
	~FPS();

private:
	Camera* camera;
	Gamepad* gamepad;

	float camX = 0, camY = 0, camZ = 0;
	float camPitch = 0;
	float camYaw = 0;

	float moveVelocity;
	float rotationVelocity;

	void moveCamera(float distance, float direction);
	void moveCameraUp(float distance, float direction);
};
