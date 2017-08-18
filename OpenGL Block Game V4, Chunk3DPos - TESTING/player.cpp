#include "player.h"
#include <iostream>

Player::Player(glm::vec3 pos, float pitch, float yaw, float roll) : pos(pos), pitch(pitch), yaw(yaw), roll(roll), 
	camera(Camera(pos, pitch, yaw, roll)), camera_mode(FIRST_PERSON_CAM), MOVEMENTSPEED(1)
{

}

Player::Player(float x, float y, float z, float pitch, float yaw, float roll) : Player(glm::vec3(x,y,z), pitch, yaw, roll)
{
	
}

inline glm::vec3& Player::get_pos()
{
	return pos;
}
inline Camera& Player::get_camera()
{
	return camera;
}

inline void Player::set_pos(glm::vec3& pos) 
{
	this->pos = pos;
}

inline void Player::set_camera(Camera& camera)
{
	this->camera = camera;
}

inline void Player::move_forward(float ds)
{
	if (camera_mode == FIRST_PERSON_CAM)
	{
		camera.move_forward(ds * MOVEMENTSPEED);
		pos.z += ds * cos(yaw) * MOVEMENTSPEED;
		pos.x -= ds * sin(yaw) * MOVEMENTSPEED;
	}
	else if (camera_mode == THIRD_PERSON_CAM)
	{
		std::cout << "TODO" << std::endl;
	}
	
}

inline void Player::move_sideways(float ds)
{
	if (camera_mode == FIRST_PERSON_CAM)
	{
		camera.move_sideways(ds * MOVEMENTSPEED);
		pos.x += ds * cos(yaw) * MOVEMENTSPEED;
		pos.z += ds * sin(yaw) * MOVEMENTSPEED;
	}
	else if (camera_mode == THIRD_PERSON_CAM)
	{
		std::cout << "TODO" << std::endl;
	}
	
}

inline void Player::move_up(float ds)
{
	if (camera_mode == FIRST_PERSON_CAM)
	{
		camera.move_up(ds * MOVEMENTSPEED);
		pos.y += ds * MOVEMENTSPEED;
	}
	else if (camera_mode == THIRD_PERSON_CAM)
	{
		std::cout << "TODO" << std::endl;
	}
	
}