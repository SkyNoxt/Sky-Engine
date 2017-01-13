
#include "FPS.h"

FPS::FPS(Camera* cam, const Gamepad* pad, float moveVel, float rotationVel)
{
	camera = cam;
	gamepad = pad;

	moveVelocity = moveVel;
	rotationVelocity = rotationVel;
}

void FPS::update()
{
	camYaw += rotationVelocity * (gamepad->state.rightThumbX);
	camPitch += rotationVelocity * (gamepad->state.rightThumbY);

	if(camPitch > 90)
		camPitch = 90;
	else if(camPitch < -90)
		camPitch = -90;
	if(camYaw < 0.0)
		camYaw += 360;
	else if(camYaw > 360.0)
		camYaw -= 360;

	moveCamera(moveVelocity * gamepad->state.leftThumbY, 0.0);
	moveCameraUp(moveVelocity * gamepad->state.leftThumbY, 0.0);
	moveCamera(moveVelocity * gamepad->state.leftThumbX, 90.0);

	camera->viewMatrix.rotate(camPitch, 1.0, 0.0, 0.0);
	camera->viewMatrix.rotate(camYaw, 0.0, 1.0, 0.0);
	camera->viewMatrix.translate(camX, camY, camZ);

	camera->cameraMatrix = camera->viewMatrix.inverse();
}

FPS::~FPS()
{
}

void FPS::moveCamera(float distance, float direction)
{
	float radians = (direction - camYaw) * Camera::DEG_TO_RAD;
	camX -= sin(radians) * distance;
	camZ -= cos(radians) * distance;
}

void FPS::moveCameraUp(float distance, float direction)
{
	float radians = (direction - camPitch) * Camera::DEG_TO_RAD;
	camY += sin(radians) * distance;
}
