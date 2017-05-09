#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
class Camera
{
public:
	Camera(glm::vec3 position, float pitch, float yaw, float roll);

	void move_forward(float ds);
	void move_sideways(float ds);
	void look_horizontal(float alpha);
	void look_vertical(float alpha);
	void move_up(float ds);

	inline glm::vec3& get_pos() { return pos; }
	inline float& get_pitch() { return pitch; }
	inline float& get_yaw() { return yaw; }
	inline float& get_roll() { return roll; }

private:
	glm::vec3 pos;
	float pitch;
	float yaw;
	float roll;
};
#endif