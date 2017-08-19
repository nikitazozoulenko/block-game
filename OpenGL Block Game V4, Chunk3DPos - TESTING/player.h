#ifndef BLOCK_GAME_PLAYER_H
#define BLOCK_GAME_PLAYER_H

#include<glm\glm.hpp>

#include "camera.h"

class Player
{
public:

	Player(glm::vec3 pos, float pitch, float yaw, float roll);
	//Player(float x, float y, float z, float pitch, float yaw, float roll);
	

	glm::vec3& get_pos();
	Camera& get_camera();
	float& get_pitch();
	float& get_yaw();
	float& get_roll();
	double& get_movementspeed();
	int& get_camera_mode();

	void set_pos(glm::vec3& pos);
	void set_camera(Camera& camera);

	void move_forward(float ds);
	void move_sideways(float ds);
	void move_up(float ds);

	void look_horizontal(const float theta);
	void look_vertical(const float theta);

	enum
	{
		FIRST_PERSON_CAM = 1,
		THIRD_PERSON_CAM = 3
	};
protected:
private:

	glm::vec3 pos;
	float pitch;
	float yaw;
	float roll;
	Camera camera;
	int camera_mode;
	double movementspeed;
	double sensitivity;

};
#endif // !BLOCK_GAME_PLAYER_H