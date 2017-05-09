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

	//get the block vao
	BlockVAOLoader loader;
	loader.MakeBlockVAO(block_vao, block_vbo, block_ebo);
}

void BlockRenderer::render(ChunkMap& chunkMap)
{
	//int count = 0;
	for (ChunkAndPosPair& chunkAndPosPair : chunkMap) {
		//std::cout << count << ": " << chunkAndPosPair.first.x << " " << chunkAndPosPair.first.y << " " << chunkAndPosPair.first.z << std::endl;
		BindVAO();
		BindTexture(2);
		PrepareBlocks(chunkAndPosPair);
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, chunkAndPosPair.second->countRenderedBlocks);
		UnbindTexture(2);
		UnbindVAO();
	}
	//std::cout << std::endl << std::endl;
}

void BlockRenderer::BindVAO()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//bind vao
	glBindVertexArray(block_vao);

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


void BlockRenderer::BindTexture(GLuint texID)
{
	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void BlockRenderer::UnbindTexture(GLuint texID)
{

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void BlockRenderer::PrepareBlocks(ChunkAndPosPair& pair_chunk_and_pos)
{
	const Chunk3DPos chunk_pos = pair_chunk_and_pos.first;
	Chunk* chunk = pair_chunk_and_pos.second;

	if (chunk->needsUpdating)
	{
		std::vector<glm::ivec3> world_positions_vector;
		for (int x = 0; x != Y_CHUNK_SIZE; ++x)
		{
			for (int y = 0; y != X_CHUNK_SIZE; ++y)
			{
				for (int z = 0; z != Z_CHUNK_SIZE; ++z)
				{
					uint16_t& block = chunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE];
					if (block)
					{
						if ((block >> 10) ^ 0x3f)
						{
							world_positions_vector.push_back(glm::ivec3(chunk_pos.x*X_CHUNK_SIZE + x, chunk_pos.y*Y_CHUNK_SIZE + y, chunk_pos.z*Z_CHUNK_SIZE + z));
						}
					}
				}
			}
		}
		chunk->countRenderedBlocks = world_positions_vector.size();
		chunk->worldPositionArray = new glm::ivec3[chunk->countRenderedBlocks];
		for (int j = 0; j != chunk->countRenderedBlocks; ++j)
		{
			chunk->worldPositionArray[j] = world_positions_vector[j];
		}
		chunk->needsUpdating = false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, block_vbo[WORLD_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, chunk->countRenderedBlocks * 3 * sizeof(int), chunk->worldPositionArray, GL_STREAM_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, block_vbo[i][WORLD_VERTEX_BUFFER], 0, chunk->worldPositionArray[i]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//void BlockRenderer::PrepareBlocks(ChunkAndPosPair& chunkAndPosPair)
//{
//	const Chunk3DPos chunkPosition = chunkAndPosPair.first;
//	Chunk* currentChunk = chunkAndPosPair.second;
//
//	if (currentChunk->needsUpdating) {
//		std::vector<glm::ivec3> world_positions_vector;
//		for (int y = 0; y != Y_CHUNK_SIZE; ++y)
//		{
//			for (int x = 0; x != X_CHUNK_SIZE; ++x)
//			{
//				for (int z = 0; z != Z_CHUNK_SIZE; ++z)
//				{
//					uint16_t& currentBlock = currentChunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE];
//
//					if (currentBlock != 0)
//					{
//						if (x != 0 && x != X_CHUNK_SIZE - 1) {
//							if (z != 0 && z != Z_CHUNK_SIZE - 1) {
//								if (y != 0 && y != Y_CHUNK_SIZE - 1) {
//									if (currentChunk->blockArray[(x + 1) + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] == 0) {
//										world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//									}
//									else if (currentChunk->blockArray[(x - 1) + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] == 0) {
//										world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//									}
//									else if (currentChunk->blockArray[x + (z + 1)*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] == 0) {
//										world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//									}
//									else if (currentChunk->blockArray[x + (z - 1)*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] == 0) {
//										world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//									}
//									else if (currentChunk->blockArray[x + z*X_CHUNK_SIZE + (y + 1)*X_CHUNK_SIZE*Z_CHUNK_SIZE] == 0) {
//										world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//									}
//									else if (currentChunk->blockArray[x + z*X_CHUNK_SIZE + (y - 1)*X_CHUNK_SIZE*Z_CHUNK_SIZE] == 0) {
//										world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//									}
//								}
//								else {
//									world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//								}
//							}
//							else {
//								world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//							}
//						}
//						else {
//							world_positions_vector.push_back(glm::ivec3(chunkPosition.x*X_CHUNK_SIZE + x, chunkPosition.y*Y_CHUNK_SIZE + y, chunkPosition.z*Z_CHUNK_SIZE + z));
//						}
//					}
//				}
//			}
//		}
//		currentChunk->countRenderedBlocks = world_positions_vector.size();
//		currentChunk->worldPositionArray = new glm::ivec3[currentChunk->countRenderedBlocks];
//		for (int i = 0; i != currentChunk->countRenderedBlocks; ++i)
//		{
//			currentChunk->worldPositionArray[i] = world_positions_vector[i];
//		}
//		currentChunk->needsUpdating = false;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, block_vbo[WORLD_VERTEX_BUFFER]);
//	glBufferData(GL_ARRAY_BUFFER, currentChunk->countRenderedBlocks * 3 * sizeof(int), currentChunk->worldPositionArray, GL_STREAM_DRAW);
//	//glBufferSubData(GL_ARRAY_BUFFER, block_vbo[WORLD_VERTEX_BUFFER], 0, world_positions);                           i dont need this??????? 
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//}

BlockRenderer::~BlockRenderer()
{

}