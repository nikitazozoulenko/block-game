#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "entityShaderprogram.h"
#include "entity.h"
#include <vector>
#include <map>

class EntityRenderer 
{
public:
	EntityRenderer(EntityShaderprogram& entityShaderprogram);
	virtual ~EntityRenderer();

	void render(std::map<Model, std::vector<Entity>>& entities);
	void render(Entity& entity); //TEMPORARY
private:
	std::map<Model, std::vector<Entity>> entities;
	EntityShaderprogram& entityShaderprogram;

	void BindVAO(Model& model);
	void UnbindVAO(Model& model);
	void BindTexture(Entity& entity);
	void UnbindTexture(Entity& entity);
	void PrepareEntity(Entity& entity);
};
#endif // ENTITYRENDERER_H
