#include "entityRenderer.h"
#include "math.h"

#include <iostream>

EntityRenderer::EntityRenderer(EntityShaderprogram& entityShaderprogram) : entityShaderprogram(entityShaderprogram)
{
	entityShaderprogram.Bind();
	entityShaderprogram.UpdateProjectionMatrix(CreateProjectionMatrix(90.0f, 4.0f / 3.0f, 0.01f, 1000.0f));
	entityShaderprogram.Unbind();
}

void EntityRenderer::render(std::map<Model, std::vector<Entity>>& entities)
{
	/*
	for (auto &pair : entities) {
		BindTexture(pair.first);
		for (Entity entity : pair.second) {
			PrepareEntity(entity);
			glDrawElements(GL_TRIANGLES, entity.get_model().get_draw_count(), GL_UNSIGNED_INT, 0);
		}
		UnbindTexture(pair.first);
	}*/
}

void EntityRenderer::render(Entity& entity)
{
	BindTexture(entity);
	PrepareEntity(entity);
	glDrawElements(GL_TRIANGLES, entity.get_model().get_draw_count(), GL_UNSIGNED_INT, 0);
	UnbindTexture(entity);
}


void EntityRenderer::BindTexture(Entity& entity)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//bind vao
	glBindVertexArray(entity.get_model().get_vao());

	//bind attribs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity.get_texID());
}

void EntityRenderer::UnbindTexture(Entity& entity)
{
	//unbind attribs
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//unbind vao
	glBindVertexArray(0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void EntityRenderer::PrepareEntity(Entity& entity)
{
	entityShaderprogram.UpdateModelMatrix(CreateModelMatrix(entity.get_world_position(), entity.get_x_rotation(), entity.get_y_rotation(), entity.get_z_rotation(), entity.get_scale()));
}

EntityRenderer::~EntityRenderer()
{
	
}