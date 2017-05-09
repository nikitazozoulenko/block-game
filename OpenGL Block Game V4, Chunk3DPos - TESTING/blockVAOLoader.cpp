#include "blockVAOLoader.h"

static int MAX_BLOCKS_RENDERING = 10000000;

BlockVAOLoader::BlockVAOLoader() {}

void BlockVAOLoader::MakeBlockVAO(GLuint& vao, GLuint* vbo_array, GLuint& ebo)
{
	Vertex vertices[] = {
		Vertex(glm::vec3(0, 1, 0), glm::vec2(1.0, 0.0), glm::vec3(0,0,-1)),
		Vertex(glm::vec3(0, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0,0,-1)),
		Vertex(glm::vec3(1, 1, 0), glm::vec2(0.0, 1.0), glm::vec3(0,0,-1)),
		Vertex(glm::vec3(1, 0, 0), glm::vec2(1.0, 1.0), glm::vec3(0,0,-1)),

		Vertex(glm::vec3(1, 1, 0), glm::vec2(1.0, 0.0), glm::vec3(1,0.0,0.0)),
		Vertex(glm::vec3(1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(1,0.0,0.0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0.0, 1.0), glm::vec3(1,0.0,0.0)),
		Vertex(glm::vec3(1, 0, 1), glm::vec2(1.0, 1.0), glm::vec3(1,0.0,0.0)),

		Vertex(glm::vec3(1, 1, 1), glm::vec2(1.0, 0.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(1, 0, 1), glm::vec2(0.0, 0.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0, 1, 1), glm::vec2(0.0, 1.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0, 0, 1), glm::vec2(1.0, 1.0), glm::vec3(0,0,1)),

		Vertex(glm::vec3(0, 1, 1), glm::vec2(0.0, 1.0), glm::vec3(-1,0.0,0.0)),
		Vertex(glm::vec3(0, 0, 1), glm::vec2(1.0, 1.0), glm::vec3(-1,0.0,0.0)),
		Vertex(glm::vec3(0, 1, 0), glm::vec2(1.0, 0.0), glm::vec3(-1,0.0,0.0)),
		Vertex(glm::vec3(0, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(-1,0.0,0.0)),

		Vertex(glm::vec3(0, 1, 1), glm::vec2(0.0, 1.0), glm::vec3(0,1,0.0)),
		Vertex(glm::vec3(0, 1, 0), glm::vec2(1.0, 1.0), glm::vec3(0,1,0.0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1.0, 0.0), glm::vec3(0,1,0.0)),
		Vertex(glm::vec3(1, 1, 0), glm::vec2(0.0, 0.0), glm::vec3(0,1,0.0)),

		Vertex(glm::vec3(1, 0, 1), glm::vec2(0.0, 1.0), glm::vec3(0,-1,0.0)),
		Vertex(glm::vec3(1, 0, 0), glm::vec2(1.0, 1.0), glm::vec3(0,-1,0.0)),
		Vertex(glm::vec3(0, 0, 1), glm::vec2(1.0, 0.0), glm::vec3(0,-1,0.0)),
		Vertex(glm::vec3(0, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0,-1,0.0))
	};
	unsigned int indices[] = {
		1,0,2,1,2,3,
		5,4,6,5,6,7,
		9,8,10,9,10,11,
		13,12,14,13,14,15,
		17,16,18,17,18,19,
		21,20,22,21,22,23
	};

	int numVertices = sizeof(vertices) / sizeof(vertices[0]);
	int numIndices = sizeof(indices) / sizeof(indices[0]);

	glm::vec3* positions = new glm::vec3[numVertices];
	glm::vec2* texCoords = new glm::vec2[numVertices];
	glm::vec3* normals = new glm::vec3[numVertices];

	for (unsigned int i = 0; i != numVertices; i++) {
		positions[i] = *(vertices[i].GetPos());
		texCoords[i] = *(vertices[i].GetTexCoord());
		normals[i] = *(vertices[i].GetNormal());
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(NUM_BUFFERS, vbo_array);
	//position
	glBindBuffer(GL_ARRAY_BUFFER, vbo_array[POSITION_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//texcoords
	glBindBuffer(GL_ARRAY_BUFFER, vbo_array[TEXCOORDS_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXCOORDS_VERTEX_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo_array[NORMAL_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(normals[0]), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//world
	glBindBuffer(GL_ARRAY_BUFFER, vbo_array[WORLD_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, MAX_BLOCKS_RENDERING * 3 * sizeof(float), nullptr, GL_STREAM_DRAW);
	glVertexAttribPointer(WORLD_VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glVertexAttribDivisor(WORLD_VERTEX_BUFFER, 1);

	//ebo, indices
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), indices, GL_STATIC_DRAW);

	//end
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	delete normals;
	delete positions;
	delete texCoords;
}

BlockVAOLoader::~BlockVAOLoader() {}