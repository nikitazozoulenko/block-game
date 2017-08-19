#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "blockShaderprogram.h"
#include "entityShaderprogram.h"
#include "blockRenderer.h"

class Camera;
class Light;

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();

	void render(Camera& camera, Light& light, ChunkMap&);
private:
	BlockShaderprogram blockShaderprogram;
	EntityShaderprogram entityShaderprogram;
	BlockRenderer blockRenderer;
};
#endif // !MASTERRENDERER_H
