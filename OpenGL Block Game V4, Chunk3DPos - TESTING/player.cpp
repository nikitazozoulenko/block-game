#include "player.h"
#include <iostream>

//class Player
//{
//public:
//	Player(glm::vec3 pos, float pitch, float yaw, float roll);
//	Player(float x, float y, float z, float pitch, float yaw, float roll);
//
//
//	inline glm::vec3& get_pos();
//	inline Camera& get_camera();
//
//	inline void set_pos(glm::vec3& pos);
//	inline void set_camera(Camera& camera);
//
//	inline void move_forward(float ds);
//	inline void move_sideways(float ds);
//	inline void move_up(float ds);
//
//protected:
//private:
//	glm::vec3 pos;
//	float pitch;
//	float yaw;
//	float roll;
//	Camera camera;
//	int camera_mode;
//	float MOVEMENTSPEED;
//
//	enum
//	{
//		FIRST_PERSON_CAM = 1,
//		THIRD_PERSON_CAM = 3
//	};
//};

Player::Player(glm::vec3 pos, float pitch, float yaw, float roll) : pos(pos), pitch(pitch), yaw(yaw), roll(roll), 
	camera(Camera(pos, pitch, yaw, roll)), camera_mode(FIRST_PERSON_CAM), MOVEMENTSPEED(1)
{

}

//Player::Player(float x, float y, float z, float pitch, float yaw, float roll) : Player(glm::vec3(x,y,z), pitch, yaw, roll)
//{
//	
//}

glm::vec3& Player::get_pos()
{
	return pos;
}
Camera& Player::get_camera()
{
	return camera;
}

void Player::set_pos(glm::vec3& pos) 
{
	this->pos = pos;
}

void Player::set_camera(Camera& camera)
{
	this->camera = camera;
}

void Player::move_forward(float ds)
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

void Player::move_sideways(float ds)
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

void Player::move_up(float ds)
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