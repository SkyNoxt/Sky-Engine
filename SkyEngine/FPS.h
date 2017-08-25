
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
	~FPS() = default;

private:
	Camera* camera;
	Gamepad* gamepad;

	Vector3<> rightVector;
	Vector3<> upVector;
	Vector3<> viewDir;
	Vector3<> position;

	float moveVelocity;
	float rotationVelocity;
};
