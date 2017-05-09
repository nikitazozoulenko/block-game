//Include GLEW  
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>

#include "entityShaderprogram.h"

EntityShaderprogram::EntityShaderprogram(std::string& vertexfile, std::string& fragmentfile)
{
	programID = glCreateProgram();
	shaders[VERTEXSHADER] = CreateShader(LoadShader(vertexfile), GL_VERTEX_SHADER);
	shaders[FRAGMENTSHADER] = CreateShader(LoadShader(fragmentfile), GL_FRAGMENT_SHADER);

	glAttachShader(programID, shaders[VERTEXSHADER]);
	glAttachShader(programID, shaders[FRAGMENTSHADER]);

	glBindAttribLocation(programID, 0, "position");
	glBindAttribLocation(programID, 1, "texCoord");

	glLinkProgram(programID);
	glBindFragDataLocation(programID, 0, "outColor");
	CheckShaderError(programID, GL_LINK_STATUS, true, "Error: Program failed to link");

	glValidateProgram(programID);
	CheckShaderError(programID, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

	uniforms[TEXTURE_SAMPLER] = glGetUniformLocation(programID, "textureSampler");
	glUniform1i(uniforms[TEXTURE_SAMPLER], 0);
	uniforms[MODEL_MATRIX] = glGetUniformLocation(programID, "modelMatrix");
	uniforms[VIEW_MATRIX] = glGetUniformLocation(programID, "viewMatrix");
	uniforms[PROJECTION_MATRIX] = glGetUniformLocation(programID, "projectionMatrix");
}

void EntityShaderprogram::UpdateModelMatrix(glm::mat4& modelMatrix)
{
	//New model matrix for every entity
	glUniformMatrix4fv(uniforms[MODEL_MATRIX], 1, GL_FALSE, &modelMatrix[0][0]);
}

void EntityShaderprogram::UpdateViewMatrix(glm::mat4& viewMatrix)
{
	//for every frame
	glUniformMatrix4fv(uniforms[VIEW_MATRIX], 1, GL_FALSE, &viewMatrix[0][0]);
}

void EntityShaderprogram::UpdateProjectionMatrix(glm::mat4& projectionMatrix)
{
	//only once i think
	glUniformMatrix4fv(uniforms[PROJECTION_MATRIX], 1, GL_FALSE, &projectionMatrix[0][0]);
}

EntityShaderprogram::~EntityShaderprogram()
{
	/*glDetachShader(programID, shaders[VERTEXSHADER]);
	glDetachShader(programID, shaders[FRAGMENTSHADER]);
	glDeleteShader(shaders[VERTEXSHADER]);
	glDeleteShader(shaders[FRAGMENTSHADER]);
	glDeleteProgram(programID);*/
}

void EntityShaderprogram::Bind()
{
	glUseProgram(programID);
}

void EntityShaderprogram::Unbind()
{
	glUseProgram(0);
}