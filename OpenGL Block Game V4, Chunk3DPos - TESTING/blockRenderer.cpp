#include "blockRenderer.h"
#include "math.h"
#include "blockVAOLoader.h"
#include "ChunkManager.h"
#include <iostream>
#include <vector>

bool world_needs_updating = true;

BlockRenderer::BlockRenderer(BlockShaderprogram& blockShaderprogram) : blockShaderprogram(blockShaderprogram)
{
	//upload projection matrix once
	blockShaderprogram.Bind();
	blockShaderprogram.UpdateProjectionMatrix(CreateProjectionMatrix(90.0f, 4.0f / 3.0f, 0.01f, 1000.0f));
	blockShaderprogram.Unbind();

	//get the block vaos
	BlockVAOLoader loader;

	//loader.MakeBlockVAO(block_vao[0], block_vbo[0], block_ebo[0]);

	loader.make_vao_UP(block_vao[Chunk::Block::UP], block_vbo[Chunk::Block::UP]);
	loader.make_vao_DOWN(block_vao[Chunk::Block::DOWN], block_vbo[Chunk::Block::DOWN]);
	loader.make_vao_NORTH(block_vao[Chunk::Block::NORTH], block_vbo[Chunk::Block::NORTH]);
	loader.make_vao_SOUTH(block_vao[Chunk::Block::SOUTH], block_vbo[Chunk::Block::SOUTH]);
	loader.make_vao_EAST(block_vao[Chunk::Block::EAST], block_vbo[Chunk::Block::EAST]);
	loader.make_vao_WEST(block_vao[Chunk::Block::WEST], block_vbo[Chunk::Block::WEST]);
}

void BlockRenderer::render(const ChunkMap& chunkMap)
{
	for (const ChunkAndPosPair& chunkAndPosPair : chunkMap) {
		for (int i = 0; i != 6; ++i)
		{
			BindVAO(i);
			BindTexture(2);
			prepare_blocks(chunkAndPosPair, i);
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, chunkAndPosPair.second->countRenderedBlocks[i]);
			UnbindTexture(2);
			UnbindVAO();
		}

	}
}

void BlockRenderer::BindVAO(int i)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//bind vao
	glBindVertexArray(block_vao[i]);

	//bind attribs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}

void BlockRenderer::UnbindVAO()
{
	//unbind attribs
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	//unbind vao
	glBindVertexArray(0);
}


void BlockRenderer::BindTexture(const GLuint texID)
{
	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void BlockRenderer::UnbindTexture(const GLuint texID)
{

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//void BlockRenderer::PrepareBlocks(const ChunkAndPosPair& const pair_chunk_and_pos, int i)
//{
//	const Chunk3DPos chunk_pos = pair_chunk_and_pos.first;
//	Chunk* chunk = pair_chunk_and_pos.second;
//
//	if (chunk->needsUpdating)
//	{
//		std::vector<glm::ivec3> world_positions_vector;
//		for (int x = 0; x != Y_CHUNK_SIZE; ++x)
//		{
//			for (int y = 0; y != X_CHUNK_SIZE; ++y)
//			{
//				for (int z = 0; z != Z_CHUNK_SIZE; ++z)
//				{
//					uint16_t& block = chunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE];
//					if (block)
//					{
//						if ((block >> 10) ^ 0x3f)
//						{
//							world_positions_vector.push_back(glm::ivec3(chunk_pos.x*X_CHUNK_SIZE + x, chunk_pos.y*Y_CHUNK_SIZE + y, chunk_pos.z*Z_CHUNK_SIZE + z));
//						}
//					}
//				}
//			}
//		}
//		chunk->countRenderedBlocks = world_positions_vector.size();
//		chunk->worldPositionArray = new glm::ivec3[chunk->countRenderedBlocks];
//		for (int j = 0; j != chunk->countRenderedBlocks; ++j)
//		{
//			chunk->worldPositionArray[j] = world_positions_vector[j];
//		}
//		chunk->needsUpdating = false;
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, block_vbo[i][WORLD_VERTEX_BUFFER]);
//	glBufferData(GL_ARRAY_BUFFER, chunk->countRenderedBlocks * 3 * sizeof(int), chunk->worldPositionArray, GL_STREAM_DRAW);
//	//glBufferSubData(GL_ARRAY_BUFFER, block_vbo[i][WORLD_VERTEX_BUFFER], 0, chunk->worldPositionArray[i]);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

void BlockRenderer::prepare_blocks(const ChunkAndPosPair& const pair_chunk_and_pos, unsigned int i)
{
	const Chunk3DPos chunk_pos = pair_chunk_and_pos.first;
	Chunk* chunk = pair_chunk_and_pos.second;
	
	if (chunk->needsUpdating[i])
	{
		std::vector<glm::ivec3> world_positions_vector;
		for (int x = 0; x != Y_CHUNK_SIZE; ++x)
		{
			for (int y = 0; y != X_CHUNK_SIZE; ++y)
			{
				for (int z = 0; z != Z_CHUNK_SIZE; ++z)
				{
					uint16_t block = chunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE];
					if (block)
					{
						if(!((block >> (15-i)) & 1))        //(((block << 4) >> 15) == 0) //                         OLD     --->>>>   ((block >> 10) ^ bitmask[i])
						{
							world_positions_vector.push_back(glm::ivec3(chunk_pos.x*X_CHUNK_SIZE + x, chunk_pos.y*Y_CHUNK_SIZE + y, chunk_pos.z*Z_CHUNK_SIZE + z));
						}
					}
				}
			}
		}
		chunk->countRenderedBlocks[i] = world_positions_vector.size();
		chunk->worldPositionArray[i] = new glm::ivec3[chunk->countRenderedBlocks[i]];
		for (int j = 0; j != chunk->countRenderedBlocks[i]; ++j)
		{
			chunk->worldPositionArray[i][j] = world_positions_vector[j];
		}
		chunk->needsUpdating[i] = false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, block_vbo[i][WORLD_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, chunk->countRenderedBlocks[i] * 3 * sizeof(int), chunk->worldPositionArray[i], GL_STREAM_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, block_vbo[i][WORLD_VERTEX_BUFFER], 0, chunk->worldPositionArray[i]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BlockRenderer::~BlockRenderer()
{

}