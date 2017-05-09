#ifndef ENTITY_H
#define ENTITY_H

#include "immovableEntity.h"

class Entity : public ImmovableEntity
{
public:
	Entity(Model &model, GLuint &texID, glm::vec3 position, float x_rot, float y_rot, float z_rot, glm::vec3 scale);

	inline void MoveForward(float ds);
	inline void MoveSideways(float ds);
private:
};

#endif