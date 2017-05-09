#include "modelLoader.h"

ModelLoader::ModelLoader() {}

Model ModelLoader::MakeModel(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices){
	//vao
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glm::vec3* positions = new glm::vec3[numVertices];
	glm::vec2* texCoords = new glm::vec2[numVertices];

	for (unsigned int i = 0; i != numVertices; i++) {
		positions[i] = *(vertices[i].GetPos());
		texCoords[i] = *(vertices[i].GetTexCoord());
	}

	//vbo
	glGenBuffers(NUM_BUFFERS + 1, vbo);
	//position
	glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//testing
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//texcoords
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORDS_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXCOORDS_VERTEX_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//testing
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//ebo, indices
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//DELETE ARRAYS????
	delete positions;
	delete texCoords;

	return Model(vao, numIndices);
}

ModelLoader::~ModelLoader()
{

}
