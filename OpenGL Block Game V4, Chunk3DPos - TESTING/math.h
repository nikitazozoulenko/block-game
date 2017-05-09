#ifndef BLOCKGAMEMATH_H
#define BLOCKGAMEMATH_H

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <cmath>

#include "camera.h"
#include <iostream>

///header-only file
static int floorFloat(float x)
{
	return x > 0 ? static_cast<int>(x) : static_cast<int>(x) - 1;
}
static glm::mat4 CreateModelMatrix(const glm::vec3& pos, const float& rx, const float& ry, const float& rz, const glm::vec3& scale)
{
	//MODEL MATRIX

	//translate
	glm::mat4 modelMatrix = glm::translate(pos);

	//rotate x
	modelMatrix = glm::rotate(
		modelMatrix,
		rx,                              //RADIANS OR DEGREE
		glm::vec3(1.0f, 0.0f, 0.0f)
	);
	//rotate y
	modelMatrix = glm::rotate(
		modelMatrix,
		ry,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	//rotate z
	modelMatrix = glm::rotate(
		modelMatrix,
		rz,
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	//scale
	modelMatrix = glm::scale(modelMatrix, scale);

	return modelMatrix;
}

static glm::mat4 CreateViewMatrix(Camera& camera)
{
	//VIEW MATRIX


	glm::mat4 viewMatrix;

	viewMatrix = glm::rotate(
		viewMatrix,
		camera.get_pitch(),
		glm::vec3(1.0f, 0.0f, 0.0f)
	);

	viewMatrix = glm::rotate(
		viewMatrix,
		camera.get_yaw(),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	viewMatrix = glm::rotate(
		viewMatrix,
		camera.get_roll(),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	viewMatrix = glm::translate(viewMatrix, -camera.get_pos());

	return viewMatrix;
}

static glm::mat4 CreateProjectionMatrix(const float& FOV, const float& aspect_ratio, const float& z_near, const float& z_far)
{

	float FOV_rad = glm::radians(FOV);
	//PROJECCTION MATRIX
	glm::mat4 projectionMatrix(glm::vec4((1.0f / std::tan(FOV_rad / 2)) / aspect_ratio, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f / std::tan(FOV_rad / 2), 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, -(z_far + z_near) / (z_far - z_near), -1.0f),
		glm::vec4(0.0f, 0.0f, -(2 * z_far*z_near) / (z_far - z_near), 0.0f));

	return projectionMatrix;
}


///OLD CODE
//static glm::mat4 CreateViewMatrix(Camera& camera)
//{
//	//VIEW MATRIX
//
//	glm::vec3 upVector(0.0f, 1.0f, 0.0f);
//	glm::vec3 lookingAt(0.0f, 0.0f, 0.0f);
//	glm::mat4 viewMatrix = glm::lookAt(
//		camera.get_pos(),	// the position of your camera, in world space
//		glm::vec3(0, 0, 0),			// where you want to look at, in world space
//		upVector			// probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
//	);
//
//	return viewMatrix;
//}
//
//static glm::mat4 CreateProjectionMatrix(const float& FOV, const float& aspect_ratio, const float& z_near, const float& z_far)
//{
//	//PROJECCTION MATRIX
//
//	glm::mat4 projectionMatrix = glm::perspective(
//		FOV,			// The horizontal Field of View, in degrees.
//		aspect_ratio,	// Aspect Ratio. Depends on the size of your window.
//		z_near,			// Near clipping plane. Keep as big as possible, or you'll get precision issues.
//		z_far			// Far clipping plane. Keep as little as possible.
//	);
//
//	return projectionMatrix;
//}

#endif // BLOCKGAMEMATH_H