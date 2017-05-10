#include "camera.h"
#define MOVEMENTSPEED 3

Camera::Camera(const glm::vec3 position, const float pitch, const float yaw, const float roll) :
	pos(position), pitch(pitch), yaw(yaw), roll(roll) {}

void Camera::move_forward(const float ds)
{
	pos.z += ds * cos(yaw) * MOVEMENTSPEED;
	pos.x -= ds * sin(yaw) * MOVEMENTSPEED;
}

void Camera::move_sideways(const float ds)
{
	pos.x += ds * cos(yaw) * MOVEMENTSPEED;
	pos.z += ds * sin(yaw) * MOVEMENTSPEED;
}

void Camera::move_up(const float ds)
{
	pos.y += ds * MOVEMENTSPEED;
}

void Camera::look_horizontal(const float alpha)
{
	yaw += alpha;
}

void Camera::look_vertical(const float alpha)
{
	pitch += alpha;
}
