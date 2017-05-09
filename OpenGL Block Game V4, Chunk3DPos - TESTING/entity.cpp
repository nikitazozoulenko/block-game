#include "entity.h"

Entity::Entity(Model &model, GLuint &texID, glm::vec3 position, float x_rot, float y_rot, float z_rot, glm::vec3 scale) : 
	ImmovableEntity(model, texID, position, x_rot, y_rot, z_rot, scale) { }

inline void Entity::MoveForward(float ds) { world_position.z += ds; }

inline void Entity::MoveSideways(float ds) { world_position.x += ds; }