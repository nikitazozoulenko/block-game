#ifndef BLOCKSHADERPROGRAM_H
#define BLOCKSHADERPROGRAM_H
#include "shaderprogram.h"

#include "camera.h"

class BlockShaderprogram : public Shaderprogram
{
public:
	BlockShaderprogram(const std::string& const, const std::string& const);

	void UpdateViewMatrix(const glm::mat4& const viewMatrix);
	void UpdateProjectionMatrix(const glm::mat4& const viewMatrix);
	void UpdateSunPos(const glm::vec3 sunPos);

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
