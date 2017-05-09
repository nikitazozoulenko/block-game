#include "blockShaderProgram.h"

BlockShaderprogram::BlockShaderprogram(std::string& vertexfile, std::string& fragmentfile)
{
	programID = glCreateProgram();
	shaders[VERTEXSHADER] = CreateShader(LoadShader(vertexfile), GL_VERTEX_SHADER);
	shaders[FRAGMENTSHADER] = CreateShader(LoadShader(fragmentfile), GL_FRAGMENT_SHADER);

	glAttachShader(programID, shaders[VERTEXSHADER]);
	glAttachShader(programID, shaders[FRAGMENTSHADER]);

	glBindAttribLocation(programID, POSITION_VERTEX_BUFFER, "position");
	glBindAttribLocation(programID, TEXCOORDS_VERTEX_BUFFER, "texCoord");
	glBindAttribLocation(programID, NORMAL_VERTEX_BUFFER, "normal");

	glBindAttribLocation(programID, WORLD_VERTEX_BUFFER, "world_pos");

	glLinkProgram(programID);
	glBindFragDataLocation(programID, 0, "outColor");
	CheckShaderError(programID, GL_LINK_STATUS, true, "Error: Program failed to link");

	glValidateProgram(programID);
	CheckShaderError(programID, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

	uniforms[TEXTURE_SAMPLER] = glGetUniformLocation(programID, "textureSampler");
	glUniform1i(uniforms[TEXTURE_SAMPLER], 0);
	uniforms[VIEW_MATRIX] = glGetUniformLocation(programID, "viewMatrix");
	uniforms[PROJECTION_MATRIX] = glGetUniformLocation(programID, "projectionMatrix");
	uniforms[SUN_POS] = glGetUniformLocation(programID, "sunPos");
}

void BlockShaderprogram::UpdateViewMatrix(glm::mat4& viewMatrix)
{
	//for every frame
	glUniformMatrix4fv(uniforms[VIEW_MATRIX], 1, GL_FALSE, &viewMatrix[0][0]);
}

void BlockShaderprogram::UpdateProjectionMatrix(glm::mat4& projectionMatrix)
{
	//only once i think
	glUniformMatrix4fv(uniforms[PROJECTION_MATRIX], 1, GL_FALSE, &projectionMatrix[0][0]);
}

void BlockShaderprogram::UpdateSunPos(glm::vec3 sunPos)
{
	//every frame
	glUniform3f(uniforms[SUN_POS], sunPos.x, sunPos.y, sunPos.z);
}

BlockShaderprogram::~BlockShaderprogram()
{
	/*glDetachShader(programID, shaders[VERTEXSHADER]);
	glDetachShader(programID, shaders[FRAGMENTSHADER]);
	glDeleteShader(shaders[VERTEXSHADER]);
	glDeleteShader(shaders[FRAGMENTSHADER]);
	glDeleteProgram(programID);*/
}