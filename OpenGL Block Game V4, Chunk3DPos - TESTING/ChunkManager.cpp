#include "ChunkManager.h"
#include <iostream>
#include <vector>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "displaywindow.h"

extern GameWorld game_world;
extern Displaywindow* p_displaywindow;

unsigned RENDER_DISTANCE_CHUNK = 8; //    greater than zero

DWORD WINAPI chunk_thread_func(void* ptr);

constexpr int MAX_THREAD_COUNT = 3;
glm::vec2* p_chunk_positions[MAX_THREAD_COUNT];

PackageChunkManagerInt* p_data[MAX_THREAD_COUNT];
DWORD   id_thread[MAX_THREAD_COUNT];
HANDLE  handle_thread[MAX_THREAD_COUNT];

ChunkManager::ChunkManager() : worldGenerator(WorldGenerator())
{
	for (int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		p_chunk_positions[i] = nullptr;
	}

	for (int i = 0; i<MAX_THREAD_COUNT; i++)
	{
		// Allocate memory for thread data.
		p_data[i] = (PackageChunkManagerInt*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PackageChunkManagerInt*));
		p_data[i]->ptr_chunk_manager = this;
		p_data[i]->i = i;

		// Create the thread to begin execution on its own.
		handle_thread[i] = CreateThread(
			NULL,                   // default security attributes
			0,                      // use default stack size  
			chunk_thread_func,       // thread function name
			p_data[i],          // argument to thread function 
			0,                      // use default creation flags 
			&id_thread[i]);   // returns the thread identifier 
	}
}

DWORD WINAPI chunk_thread_func(void* ptr)
{
	PackageChunkManagerInt* data = (PackageChunkManagerInt*) ptr;
	int i = data->i;

	while (!(p_displaywindow->ShouldClose()))
	{
		if (p_chunk_positions[i] != nullptr)
		{
			data->ptr_chunk_manager->create_chunk(*(p_chunk_positions[i]));
			delete p_chunk_positions[i];
			p_chunk_positions[i] = nullptr;
		}
	}
	return 0;
}

void ChunkManager::create_chunk(const int x, const int z)
{
	Position2D position(x, z);
	game_world.chunk_map[position] = init_chunk(worldGenerator.gen_chunk_at_pos(x, z), position);
}

void ChunkManager::create_chunk(const glm::vec2 pos)
{
	create_chunk(pos.x, pos.y);
}

Chunk* ChunkManager::init_chunk(Chunk* const chunk, const Position2D& const position)
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
							/*if (worldGenerator.simplex_noise(position.x + static_cast<float>(x + 1) / X_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
							{
								uint16_t add = 0b0000010000000000;
								currentBlock += add;

							}*/
							if (chunk->blockArray[(x - 1) + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0000100000000000;
								currentBlock += add;

							}
						}
					}
					else
					{
						/*if (worldGenerator.simplex_noise(position.x + static_cast<float>(x - 1) / X_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
						{
							uint16_t add = 0b0000100000000000;
							currentBlock += add;

						}*/
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
							/*if (worldGenerator.simplex_noise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
							{
								uint16_t add = 0b0001000000000000;
								currentBlock += add;
							}*/
							if (chunk->blockArray[x + z*X_CHUNK_SIZE + (y - 1)*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b0010000000000000;
								currentBlock += add;
							}
						}
					}
					else
					{
						/*if (worldGenerator.simplex_noise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.z + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
						{
							uint16_t add = 0b0010000000000000;
							currentBlock += add;
						}*/
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
							/*if (worldGenerator.simplex_noise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.z + static_cast<float>(z + 1) / Z_CHUNK_SIZE) < -0.1)
							{
								uint16_t add = 0b0100000000000000;
								currentBlock += add;

							}*/
							if (chunk->blockArray[x + (z - 1)*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] != 0)
							{
								uint16_t add = 0b1000000000000000;
								currentBlock += add;
							}
						}
					}
					else
					{
						/*if (worldGenerator.simplex_noise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, position.z + static_cast<float>(z - 1) / Z_CHUNK_SIZE) < -0.1)
						{
							uint16_t add = 0b1000000000000000;
							currentBlock += add;
						}*/
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

void ChunkManager::search_and_create_chunk(int x, int z)
{
	auto search = game_world.chunk_map.find(Position2D(x, z));
	if (search == game_world.chunk_map.end())
	{
		create_chunk(x, z);
	}
}

void ChunkManager::loop()
{
	glm::vec3 playerpos = game_world.player.get_camera().get_pos();

	int x = playerpos.x / X_CHUNK_SIZE;
	if (playerpos.x < 0)
	{
		--x;
	}
	int z = playerpos.z / Z_CHUNK_SIZE;
	if (playerpos.z < 0)
	{
		--z;
	}

	//start search loop
	int count = 0;
	auto search = game_world.chunk_map.find(Position2D(x, z));
	if (search == game_world.chunk_map.end())
	{
		p_chunk_positions[count] = new glm::vec2(x, z);
		++count;
	}
	x--;
	z++;
	for (int i = 1; i < RENDER_DISTANCE_CHUNK; ++i)
	{
		for (int j = 0; j != i * 2; j++)
		{
			if (count == MAX_THREAD_COUNT)
			{
				count = 0;
				goto endloop;
				
			}
			else
			{
				auto search = game_world.chunk_map.find(Position2D(x, z));
				if (search == game_world.chunk_map.end())
				{
					p_chunk_positions[count] = new glm::vec2(x, z);
					++count;
				}
				x++;
			}
		}
		for (int j = 0; j != i * 2; j++)
		{
			if (count == MAX_THREAD_COUNT)
			{
				count = 0;
				goto endloop;
			}
			else
			{
				auto search = game_world.chunk_map.find(Position2D(x, z));
				if (search == game_world.chunk_map.end())
				{
					p_chunk_positions[count] = new glm::vec2(x, z);
					++count;
				}
				z--;
			}
		}
		for (int j = 0; j != i * 2; j++)
		{
			if (count == MAX_THREAD_COUNT)
			{
				count = 0;
				goto endloop;
			}
			else
			{
				auto search = game_world.chunk_map.find(Position2D(x, z));
				if (search == game_world.chunk_map.end())
				{
					p_chunk_positions[count] = new glm::vec2(x, z);
					++count;
				}
				x--;
			}
		}
		for (int j = 0; j != i * 2; j++)
		{
			if (count == MAX_THREAD_COUNT)
			{
				count = 0;
				goto endloop;
			}
			else
			{
				auto search = game_world.chunk_map.find(Position2D(x, z));
				if (search == game_world.chunk_map.end())
				{
					p_chunk_positions[count] = new glm::vec2(x, z);
					++count;
				}
				z++;
			}
		}
		x--;
		z++;
	}
	endloop:
	;
	//endloop
}

void ChunkManager::unload_chunk(Chunk* chunk, const Position2D pos)
{
	game_world.chunk_map.erase(pos);
	delete chunk;
}