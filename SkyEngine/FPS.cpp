
#include <cmath>

#include "FPS.h"

FPS::FPS(Camera* cam, Gamepad* pad, float moveVel, float rotationVel)
	: camera(cam)
	, gamepad(pad)
	, rightVector({ 1, 0, 0 })
	, upVector({ 0, 1, 0 })
	, viewDir({ 0, 0, 1 })
	, position({ 0, 0, 0 })
	, moveVelocity(moveVel)
	, rotationVelocity(rotationVel)
{
}

void FPS::update()
{
	float pitchAngle = rotationVelocity * -gamepad->state.rightThumbY;
	float yawAngle = rotationVelocity * gamepad->state.rightThumbX;
	float rollAngle = rotationVelocity * (gamepad->state.leftTrigger - gamepad->state.rightTrigger);

	float zMovement = moveVelocity * -gamepad->state.leftThumbY;
	float yMovement = 0;
	float xMovement = moveVelocity * gamepad->state.leftThumbX;

	//Pitch
	viewDir = (viewDir * std::cos(pitchAngle * Camera::DEG_TO_RAD) -
		upVector * std::sin(pitchAngle * Camera::DEG_TO_RAD)
	 ).normalize();
  
	 upVector = viewDir.cross(rightVector);
	//

	//Yaw
	viewDir = (viewDir * std::cos(yawAngle * Camera::DEG_TO_RAD) -
		rightVector * std::sin(yawAngle * Camera::DEG_TO_RAD)
	 ).normalize();
  
	 rightVector = -viewDir.cross(upVector);
	//

	//Roll
	rightVector = (rightVector * std::cos(rollAngle * Camera::DEG_TO_RAD) -
		upVector * std::sin(rollAngle * Camera::DEG_TO_RAD)
	 ).normalize();
  
	 upVector = viewDir.cross(rightVector);
	//

	//Move
	position += (rightVector * xMovement);
	position += (upVector * yMovement);
	position -= (viewDir * zMovement);
	//
	
	Vector3<> viewPoint = position - viewDir;
		   
	camera->cameraMatrix = Matrix4<>(position, viewPoint, upVector);
	camera->viewMatrix = camera->cameraMatrix.inverse();

}
