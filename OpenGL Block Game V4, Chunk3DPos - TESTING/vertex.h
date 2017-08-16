#ifndef VERTEX_BLOCK_GAME_H
#define VERTEX_BLOCK_GAME_H

#include <GL\glew.h>
#include <glm/glm.hpp>

class Vertex
{
public:
	Vertex(const glm::vec3&position, const glm::vec2& texCoordinates, const glm::vec3& normalVector) : pos(position), texCoord(texCoordinates), normal(normalVector) {}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }

private:
	//vertex attributes
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

#endif // !VERTEX_BLOCK_GAME_H
