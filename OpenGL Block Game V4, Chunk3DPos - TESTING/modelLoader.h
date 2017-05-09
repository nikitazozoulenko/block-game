#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "model.h"

class ModelLoader 
{
public:
	ModelLoader();

	Model MakeModel(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Model MakeBlockVAO();

	~ModelLoader();
private:

	//enum for the vertex buffer objects
	enum
	{
		POSITION_VERTEX_BUFFER,
		TEXCOORDS_VERTEX_BUFFER,

		NUM_BUFFERS
	};

	//IDs for buffers
	GLuint vbo[NUM_BUFFERS];
	GLuint ebo;
};

#endif // !MODELLOADER_H
