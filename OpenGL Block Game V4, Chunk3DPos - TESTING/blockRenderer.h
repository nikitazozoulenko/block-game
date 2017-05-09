#ifndef BLOCKRENDERER_H
#define BLOCKRENDERER_H

#include "blockShaderprogram.h"
#include "ChunkManager.h"

class BlockRenderer
{
public:
	BlockRenderer(BlockShaderprogram& blockShaderprogram);
	virtual ~BlockRenderer();

	void render(ChunkMap& chunkMap);

private:
	BlockShaderprogram& blockShaderprogram;

	void BindVAO();
	void UnbindVAO();
	void BindTexture(GLuint texID);
	void UnbindTexture(GLuint texID);
	void PrepareBlocks(ChunkAndPosPair& chunkAndPosPair);

	//enum for the vertex buffer objects
	enum
	{
		POSITION_VERTEX_BUFFER,
		TEXCOORDS_VERTEX_BUFFER,
		NORMAL_VERTEX_BUFFER,

		WORLD_VERTEX_BUFFER,

		NUM_BUFFERS
	};

	//IDs for buffers
	GLuint block_vao;
	GLuint block_vbo[NUM_BUFFERS];
	GLuint block_ebo;
};

#endif // !BLOCKRENDERER_H