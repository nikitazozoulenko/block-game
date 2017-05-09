#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "blockShaderprogram.h"
#include "entityShaderprogram.h"
#include "blockRenderer.h"
#include "entityRenderer.h"
#include "light.h"
#include "ChunkManager.h"

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();

	void render(Camera& camera, Light& light, ChunkMap&);
private:
	BlockShaderprogram blockShaderprogram;
	EntityShaderprogram entityShaderprogram;
	BlockRenderer blockRenderer;
	EntityRenderer entityRenderer;
};
#endif // !MASTERRENDERER_H
