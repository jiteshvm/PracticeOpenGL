#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;

	updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement MovementDirection, float DeltaTime)
{
	float velocity = MovementSpeed * DeltaTime;
	if (MovementDirection == FORWARD)
		Position += Front * velocity;
	if (MovementDirection == BACKWARD)
		Position -= Front * velocity;
	if (MovementDirection == LEFT)
		Position -= Right * velocity;
	if (MovementDirection == RIGHT)
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constraintPitch)
{
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constraintPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	float PitchRadians = glm::radians(Pitch);
	float YawRadians = glm::radians(Yaw);
	front.x = cos(PitchRadians) * cos(YawRadians);
	front.y = sin(PitchRadians);
	front.z = cos(PitchRadians) * sin(YawRadians);
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}