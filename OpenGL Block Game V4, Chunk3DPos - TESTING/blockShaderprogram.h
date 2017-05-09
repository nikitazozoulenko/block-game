#ifndef BLOCKSHADERPROGRAM_H
#define BLOCKSHADERPROGRAM_H
#include "shaderprogram.h"

#include "camera.h"

class BlockShaderprogram : public Shaderprogram
{
public:
	BlockShaderprogram(std::string &, std::string &);

	void UpdateViewMatrix(glm::mat4& viewMatrix);
	void UpdateProjectionMatrix(glm::mat4& viewMatrix);
	void UpdateSunPos(glm::vec3 sunPos);

	virtual ~BlockShaderprogram();
protected:
private:

	//vao attribs
	enum
	{
		POSITION_VERTEX_BUFFER,
		TEXCOORDS_VERTEX_BUFFER,
		NORMAL_VERTEX_BUFFER,

		WORLD_VERTEX_BUFFER,

		NUM_BUFFERS
	};

	//all program's UNIFORMS
	enum
	{
		TEXTURE_SAMPLER,
		VIEW_MATRIX,
		PROJECTION_MATRIX,
		SUN_POS,

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
#endif // !BLOCKSHADERPROGRAM_H
