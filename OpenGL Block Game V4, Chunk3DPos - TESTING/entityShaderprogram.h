#ifndef ENTITYSHADERPROGRAM_H
#define ENTITYSHADERPROGRAM_H

//Include GLEW  
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>

#include "shaderprogram.h"
#include "camera.h"

class EntityShaderprogram : public Shaderprogram 
{
public:
	EntityShaderprogram(std::string &, std::string &);

	void Bind();
	void Unbind();

	void UpdateModelMatrix(glm::mat4& ModelMatrix);
	void UpdateViewMatrix(glm::mat4& viewMatrix);
	void UpdateProjectionMatrix(glm::mat4& viewMatrix);

	virtual ~EntityShaderprogram();
protected:
private:
	//programID
	GLuint programID;

	//all program's UNIFORMS
	enum
	{
		TEXTURE_SAMPLER,
		MODEL_MATRIX,
		VIEW_MATRIX,
		PROJECTION_MATRIX,

		NUM_UNIFORMS
	};
	GLuint uniforms[NUM_UNIFORMS];

	//the program's SHADERS
	enum
	{
		VERTEXSHADER,
		FRAGMENTSHADER,

		NUM_SHADERS
	};
	GLuint shaders[NUM_SHADERS];
};

#endif // ENTITYSHADERPROGRAM_H