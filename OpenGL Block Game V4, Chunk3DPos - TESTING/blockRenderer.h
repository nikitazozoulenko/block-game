#ifndef BLOCKRENDERER_H
#define BLOCKRENDERER_H

#include "blockShaderprogram.h"
#include "ChunkManager.h"

class BlockRenderer
{
public:
	BlockRenderer(BlockShaderprogram& const blockShaderprogram);
	virtual ~BlockRenderer();

	void render(ChunkMap& const chunkMap);

private:
	BlockShaderprogram& blockShaderprogram;

	void BindVAO();
	void UnbindVAO();
	void BindTexture(const GLuint texID);
	void UnbindTexture(const GLuint texID);
	void PrepareBlocks(ChunkAndPosPair& const chunkAndPosPair);

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