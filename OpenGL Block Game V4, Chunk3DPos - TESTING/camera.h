#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
class Camera
{
public:
	Camera(const glm::vec3 position, const float pitch, const float yaw, const float roll);

	void move_forward(const float ds);
	void move_sideways(const float ds);
	void look_horizontal(const float alpha);
	void look_vertical(const float alpha);
	void move_up(const float ds);

	inline glm::vec3& get_pos() { return pos; }
	inline float& get_pitch() { return pitch; }
	inline float& get_yaw() { return yaw; }
	inline float& get_roll() { return roll; }

	inline void set_pitch(float new_pitch) { pitch = new_pitch; }
	inline void set_yaw(float new_yaw) { yaw = new_yaw; }
	inline void set_pos(glm::vec3 new_pos) { pos = new_pos; }

private:
	glm::vec3 pos;
	float pitch;
	float yaw;
	float roll;
};
#endif