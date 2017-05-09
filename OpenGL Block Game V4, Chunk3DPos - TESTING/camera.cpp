#include "camera.h"
#define MOVEMENTSPEED 3

Camera::Camera(glm::vec3 position, float pitch, float yaw, float roll) : 
	pos(position), pitch(pitch), yaw(yaw), roll(roll) {}

void Camera::move_forward(float ds)
{
	pos.z += ds * cos(yaw) * MOVEMENTSPEED;
	pos.x -= ds * sin(yaw) * MOVEMENTSPEED;
}

void Camera::move_sideways(float ds)
{
	pos.x += ds * cos(yaw) * MOVEMENTSPEED;
	pos.z += ds * sin(yaw) * MOVEMENTSPEED;
}

void Camera::move_up(float ds)
{
	pos.y += ds * MOVEMENTSPEED;
}

void Camera::look_horizontal(float alpha)
{
	yaw += alpha;
}

void Camera::look_vertical(float alpha)
{
	pitch += alpha;
}

