#ifndef LIGHT_H
#define LIGHT_H

#include <glm\glm.hpp>

class Light {
public:
	Light(const glm::vec3 worldposition);

	inline glm::vec3& GetPos() { return pos; };
	inline void SetPos(glm::vec3& pos) { this->pos = pos; }
protected:
private:
	glm::vec3 pos;
};

#endif