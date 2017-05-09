#ifndef BLOCKVAOLOADER_H
#define BLOCKVAOLOADER_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "model.h"

class BlockVAOLoader
{
public:
	BlockVAOLoader();

	void MakeBlockVAO(GLuint& vao, GLuint* vbo_array, GLuint& ebo);

	~BlockVAOLoader();

private:

	//enum for the vertex buffer objects
	enum
	{
		POSITION_VERTEX_BUFFER,
		TEXCOORDS_VERTEX_BUFFER,
		NORMAL_VERTEX_BUFFER,

		WORLD_VERTEX_BUFFER,

		NUM_BUFFERS
	};

};
#endif // !BLOCKVAOLOADER_H
