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

	void set_pos(glm::vec3& pos);
	void set_camera(Camera& camera);

	void move_forward(float ds);
	void move_sideways(float ds);
	void move_up(float ds);

protected:
private:
	glm::vec3 pos;
	float pitch;
	float yaw;
	float roll;
	Camera camera;
	int camera_mode;
	float MOVEMENTSPEED;

	enum 
	{
		FIRST_PERSON_CAM = 1,
		THIRD_PERSON_CAM = 3
	};
};
#endif // !BLOCK_GAME_PLAYER_H