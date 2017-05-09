#ifndef MODEL_H
#define MODEL_H

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

class Model 
{
public:
	Model(GLuint& vao, unsigned int& draw_count) : vao(vao), draw_count(draw_count) {}
	Model(const Model& model) : vao(model.vao), draw_count(model.draw_count) {}
	Model(int i) : vao(i), draw_count(i) {}
	virtual ~Model() { }

	inline unsigned int& get_draw_count() { return draw_count; }
	inline GLuint& get_vao() { return vao; }

private:
	//the models's vao
	GLuint vao;

	//draw count
	unsigned int draw_count;
};

#endif //MODEL_H