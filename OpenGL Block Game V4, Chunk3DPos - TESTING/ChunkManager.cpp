#include "ChunkManager.h"
#include <iostream>

Camera zerocam2 = Camera(glm::vec3(0, 0, 0), 0.0f, 0.0f, 0.0f);
Camera& ChunkManager::camera = zerocam2;

ChunkManager::ChunkManager(const Camera& const camera) : worldGenerator(WorldGenerator())
{
	//map is default initialized

	//init camera
	InitStaticCamera(camera);
}

void ChunkManager::InitStaticCamera(const Camera& const other_camera)
{
	camera = other_camera;
}

void ChunkManager::create_chunk(const int x, const int y, const int z)
{
	Chunk3DPos position(x, y, z);
	chunkMap[position] = init_chunk(worldGenerator.GenChunkAtPosition(x, y, z), position);
}

Chunk* ChunkManager::init_chunk(Chunk* const chunk, const Chunk3DPos& const position)
{
	for (int x = 0; x != Y_CHUNK_SIZE; ++x)
	{
		for (int y = 0; y != X_CHUNK_SIZE; ++y)
		{
			for (int z = 0; z != Z_CHUNK_SIZE; ++z)
			{
				uint16_t& const currentBlock = chunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE];
				if (currentBlock == 1)
				{
					if (x != 0)
					{
						if (x != X_CHUNK_SIZE - 1)
						{
							if (chunk->blockArray[(x + 1) + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0000010000000000;
								currentBlock += add;
							}
							if (chunk->blockArray[(x - 1) + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0000100000000000;
								currentBlock += add;
							}
						}
						else
						{
							if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x+1) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
							{
								uint16_t add = 0b0000010000000000;
								currentBlock += add;
							}
							if (chunk->blockArray[(x - 1) + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0000100000000000;
								currentBlock += add;
							}
						}
					}
					else
					{
						if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x-1) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
						{
							uint16_t add = 0b0000100000000000;
							currentBlock += add;
						}
						if (chunk->blockArray[(x + 1) + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
						{
							uint16_t add = 0b0000010000000000;
							currentBlock += add;
						}
					}
					if (y != 0)
					{
						if (y != Y_CHUNK_SIZE - 1)
						{
							if (chunk->blockArray[x + z*X_CHUNK_SIZE + (y + 1)*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0001000000000000;
								currentBlock += add;
							}
							if (chunk->blockArray[x + z*X_CHUNK_SIZE + (y - 1)*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0010000000000000;
								currentBlock += add;
							}
						}
						else
						{
							if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y+1) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
							{
								uint16_t add = 0b0001000000000000;
								currentBlock += add;
							}
							if (chunk->blockArray[x + z*X_CHUNK_SIZE + (y - 1)*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0010000000000000;
								currentBlock += add;
							}
						}
					}
					else
					{
						if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y-1) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
						{
							uint16_t add = 0b0010000000000000;
							currentBlock += add;
						}
						if (chunk->blockArray[x + z*X_CHUNK_SIZE + (y + 1)*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
						{
							uint16_t add = 0b0001000000000000;
							currentBlock += add;
						}
					}
					if (z != 0)
					{
						if (z != Z_CHUNK_SIZE - 1)
						{
							if (chunk->blockArray[x + (z + 1)*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0100000000000000;
								currentBlock += add;
							}
							if (chunk->blockArray[x + (z - 1)*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b1000000000000000;
								currentBlock += add;
							}
						}
						else
						{
							if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z+1) / Z_CHUNK_SIZE) < -0.1)
							{
								uint16_t add = 0b0100000000000000;
								currentBlock += add;
							}
							if (chunk->blockArray[x + (z - 1)*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b1000000000000000;
								currentBlock += add;
							}
						}
					}
					else
					{
						if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z-1) / Z_CHUNK_SIZE) < -0.1)
						{
							uint16_t add = 0b1000000000000000;
							currentBlock += add;
						}
						if (chunk->blockArray[x + (z + 1)*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
						{
							uint16_t add = 0b0100000000000000;
							currentBlock += add;
						}
					}
				}
			}
		}
	}

	return chunk;
}