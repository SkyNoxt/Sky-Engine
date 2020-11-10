
#pragma once

#include <Camera/Camera.h>
#include <Input/Gamepad.h>

class FPS
{

  public:
	//Constructor
	FPS(Camera* cam, Gamepad* pad, float moveSpd = 1.0, float rotationSpd = 1.0);

	//Member function
	void update();

	//Destructor
	~FPS() = default;

  //private:
	Camera* camera;
	Gamepad* gamepad;

	Vector3<> right;
	Vector3<> up;
	Vector3<> view;
	Vector3<> position;

	float moveSpeed;
	float rotationSpeed;
};
