#ifndef IMMOVABLEENTITY_H
#define IMMOVABLEENTITY_H

#include "model.h"

class ImmovableEntity
{
public:
	ImmovableEntity(Model &model, GLuint &texID, glm::vec3 position, float x_rot, float y_rot, float z_rot, glm::vec3 scale) :
		model(model), texID(texID), world_position(position), x_rotation(x_rot), y_rotation(y_rot), z_rotation(z_rot), scale(scale) {}

	inline Model& get_model() { return model; }
	inline GLuint& get_texID() { return texID; }
	inline glm::vec3 get_world_position() { return world_position; }
	inline float& get_x_rotation() { return x_rotation; }
	inline float& get_y_rotation() { return y_rotation; }
	inline float& get_z_rotation() { return z_rotation; }
	inline glm::vec3 get_scale() { return scale; }

protected:
	//model
    Model& model;
	//texture
	GLuint& texID;

	//positional data
	glm::vec3 world_position;
	float x_rotation;
	float y_rotation;
	float z_rotation;
	glm::vec3 scale;

private:
};

#endif // !IMMOVABLEENTITY_H
