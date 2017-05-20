#ifndef BLOCKRENDERER_H
#define BLOCKRENDERER_H

#include "blockShaderprogram.h"
#include "ChunkManager.h"
#include "Chunk.h"

class BlockRenderer
{
public:
	BlockRenderer(BlockShaderprogram& blockShaderprogram);
	virtual ~BlockRenderer();

	void render(const ChunkMap& chunkMap, Camera& camera);

private:
	BlockShaderprogram& blockShaderprogram;

	void BindVAO(int i);
	void UnbindVAO();
	void BindTexture(const GLuint texID);
	void UnbindTexture(const GLuint texID);
	//void PrepareBlocks(const ChunkAndPosPair& const chunkAndPosPair, int i);
	void prepare_blocks(const ChunkAndPosPair& const pair_chunk_and_pos, unsigned int i);

	uint16_t bitmask[6] = { 1 << 5, 1 << 4, 1 << 3, 1 << 2, 1 << 1, 1 << 0 };

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
	GLuint block_vao[Chunk::Block::NUM_DIRECTIONS];
	GLuint block_vbo[Chunk::Block::NUM_DIRECTIONS][NUM_BUFFERS];
	GLuint block_ebo[Chunk::Block::NUM_DIRECTIONS];
};

#endif // !BLOCKRENDERER_H