#include "ChunkManager.h"
#include <iostream>
#include <vector>

unsigned RENDER_DISTANCE_CHUNK = 3;

ChunkManager::ChunkManager(Camera& const camera) : worldGenerator(WorldGenerator()), camera(camera)
{

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
							if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x + 1) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
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
						if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x - 1) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
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
							if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y + 1) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
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
						if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y - 1) / Y_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
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
							if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z + 1) / Z_CHUNK_SIZE) < -0.1)
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
						if (worldGenerator.SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.y + static_cast<float>(y) / Y_CHUNK_SIZE, position.z + static_cast<float>(z - 1) / Z_CHUNK_SIZE) < -0.1)
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

void ChunkManager::loop()
{
	std::vector<ChunkAndPosPair> vector_needs_deleting;

	int player_x = camera.get_pos().x / X_CHUNK_SIZE;
	if (camera.get_pos().x < 0)
	{
		--player_x;
	}
	int player_y = camera.get_pos().y / X_CHUNK_SIZE;
	if (camera.get_pos().y < 0)
	{
		--player_y;
	}
	int player_z = camera.get_pos().z / X_CHUNK_SIZE;
	if (camera.get_pos().z < 0)
	{
		--player_z;
	}

	int lower_bound_x = player_x - RENDER_DISTANCE_CHUNK;
	int higher_bound_x = player_x + RENDER_DISTANCE_CHUNK;
	int lower_bound_y = player_y - RENDER_DISTANCE_CHUNK;
	int higher_bound_y = player_y + RENDER_DISTANCE_CHUNK;
	int lower_bound_z = player_z - RENDER_DISTANCE_CHUNK;
	int higher_bound_z = player_z + RENDER_DISTANCE_CHUNK;

	for (int n = lower_bound_x; n <= higher_bound_x; ++n)
	{
		for (int m = lower_bound_y; m <= higher_bound_y; ++m)
		{
			for (int k = lower_bound_z; k <= higher_bound_z; ++k)
			{
				auto search = chunkMap.find(Chunk3DPos(n, m, k));
				if (search != chunkMap.end())
				{
					//std::cout << "Found chunk " << search->first.x << " " << search->first.y << " " << search->first.z << "       " << search->second << '\n';
				}
				else
				{
					//std::cout << "Not found, creating chunk\n";
					create_chunk(n, m, k);
				}

				//std::cout << "Player: " << player_x << " " << player_y << " " << player_z << "\n";
			}
		}
	}

}

void ChunkManager::unload_chunk(Chunk* chunk, const Chunk3DPos pos)
{
	chunkMap.erase(pos);
	delete chunk;
}