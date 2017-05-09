#include "masterRenderer.h"
#include "math.h"

MasterRenderer::MasterRenderer() :
	blockShaderprogram(BlockShaderprogram(std::string("blockVertexShader.txt"), std::string("blockFragmentShader.txt"))),
	entityShaderprogram(EntityShaderprogram(std::string("entityVertexShader.txt"), std::string("entityFragmentShader.txt"))),
	blockRenderer(blockShaderprogram),
	entityRenderer(entityShaderprogram)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//TEMPORARY?????
	glEnable(GL_DEPTH_TEST);
}

void MasterRenderer::render(Camera& camera, Light& light, ChunkMap& chunkMap)
{
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//BLOCKS
	blockShaderprogram.Bind();
	blockShaderprogram.UpdateSunPos(light.GetPos());
	blockShaderprogram.UpdateViewMatrix(CreateViewMatrix(camera));
	blockRenderer.render(chunkMap);
	blockShaderprogram.Unbind();


	//ENTITIES
	entityShaderprogram.Bind();
	entityShaderprogram.UpdateViewMatrix(CreateViewMatrix(camera));
	///entityRenderer.render(entity);
	entityShaderprogram.Unbind();

}

MasterRenderer::~MasterRenderer()
{

}