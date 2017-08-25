
#include <cmath>

#include "FPS.h"

FPS::FPS(Camera* cam, Gamepad* pad, float moveSpd, float rotationSpd)
	: camera(cam)
	, gamepad(pad)
	, right({ 1, 0, 0 })
	, up({ 0, 1, 0 })
	, view({ 0, 0, 1 })
	, position({ 0, 0, 0 })
	, moveSpeed(moveSpd)
	, rotationSpeed(rotationSpd)
{
}

void FPS::update()
{
	float pitchAngle = rotationSpeed * -gamepad->state.rightThumbY;
	float yawAngle = rotationSpeed * gamepad->state.rightThumbX;
	float rollAngle = rotationSpeed * (gamepad->state.leftTrigger - gamepad->state.rightTrigger);

	float zMovement = moveSpeed * -gamepad->state.leftThumbY;
	float yMovement = 0;
	float xMovement = moveSpeed * gamepad->state.leftThumbX;

	//Pitch
	view = (view * std::cos(pitchAngle * Camera::DEG_TO_RAD) - up * std::sin(pitchAngle * Camera::DEG_TO_RAD)).normalize();
	up = view.cross(right);
	//

	//Yaw
	view = (view * std::cos(yawAngle * Camera::DEG_TO_RAD) - right * std::sin(yawAngle * Camera::DEG_TO_RAD)).normalize();
	right = -view.cross(up);
	//

	//Roll
	right = (right * std::cos(rollAngle * Camera::DEG_TO_RAD) - up * std::sin(rollAngle * Camera::DEG_TO_RAD)).normalize();
	up = view.cross(right);
	//

	//Move
	position += (right * xMovement);
	position += (up * yMovement);
	position -= (view * zMovement);
	//

	Vector3<> viewPoint = position - view;
	camera->cameraMatrix = Matrix4<>(position, viewPoint, up);
	camera->viewMatrix = camera->cameraMatrix.inverse();
}
