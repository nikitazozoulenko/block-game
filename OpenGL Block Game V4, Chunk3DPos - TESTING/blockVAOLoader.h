#ifndef BLOCKVAOLOADER_H
#define BLOCKVAOLOADER_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "vertex.h"

class BlockVAOLoader
{
public:
	BlockVAOLoader();

	void MakeBlockVAO(GLuint& vao, GLuint* vbo_array, GLuint& ebo);

	void make_vao_UP(GLuint& vao, GLuint* vbo_array);
	void make_vao_DOWN(GLuint& vao, GLuint* vbo_array);
	void make_vao_NORTH(GLuint& vao, GLuint* vbo_array);
	void make_vao_SOUTH(GLuint& vao, GLuint* vbo_array);
	void make_vao_EAST(GLuint& vao, GLuint* vbo_array);
	void make_vao_WEST(GLuint& vao, GLuint* vbo_array);

	~BlockVAOLoader();

private:

	void load_vao(GLuint& vao, GLuint* vbo_array, GLuint& ebo, Vertex* vertices, unsigned int* indices, int numVertices, int numIndices);
	void load_vao222(GLuint& vao, GLuint* vbo_array, Vertex* vertices,  int numVertices);

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
