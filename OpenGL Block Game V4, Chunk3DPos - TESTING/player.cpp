#include "player.h"
#include <iostream>
#include <glm\gtc\constants.hpp>

Player::Player(glm::vec3 pos, float pitch, float yaw, float roll) : pos(pos), pitch(pitch), yaw(yaw), roll(roll), 
	camera(Camera(pos, pitch, yaw, roll)), camera_mode(FIRST_PERSON_CAM), movementspeed(5), sensitivity(0.005)
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

float& Player::get_pitch()
{
	return pitch;
}
float& Player::get_yaw()
{
	return yaw;
}
float& Player::get_roll()
{
	return roll;
}

double& Player::get_movementspeed()
{
	return movementspeed;
}

int& Player::get_camera_mode()
{
	return camera_mode;
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
		camera.move_forward(ds * movementspeed);
		pos.z += ds * cos(yaw) * movementspeed;
		pos.x -= ds * sin(yaw) * movementspeed;
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
		camera.move_sideways(ds * movementspeed);
		pos.x += ds * cos(yaw) * movementspeed;
		pos.z += ds * sin(yaw) * movementspeed;
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
		camera.move_up(ds * movementspeed);
		pos.y += ds * movementspeed;
	}
	else if (camera_mode == THIRD_PERSON_CAM)
	{
		std::cout << "TODO" << std::endl;
	}
	
}

void Player::look_horizontal(const float theta)
{
	if (camera_mode == FIRST_PERSON_CAM)
	{
		yaw += theta * sensitivity;
		camera.set_yaw(yaw);
		std::cout << "TEST";
	}
	else if (camera_mode == THIRD_PERSON_CAM)
	{
		std::cout << "TODO" << std::endl;
	}
	
}

void Player::look_vertical(const float theta)
{
	if (camera_mode == FIRST_PERSON_CAM)
	{
		float next_pitch = pitch + theta * sensitivity;
		if (next_pitch < glm::pi<float>()/2 && next_pitch > -glm::pi<float>()/2)
		{
			pitch = next_pitch;
			camera.set_pitch(pitch);
		}
	}
	else if (camera_mode == THIRD_PERSON_CAM)
	{
		std::cout << "TODO" << std::endl;
	}
	
}