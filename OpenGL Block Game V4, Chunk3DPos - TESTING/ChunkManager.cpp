#include "ChunkManager.h"
#include <iostream>
#include <vector>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

extern GameWorld game_world;

unsigned RENDER_DISTANCE_CHUNK = 3;
constexpr int MAX_CHUNK_THREADS = 1;
extern void ErrorHandler(LPTSTR lpszFunction);
DWORD WINAPI create_chunk_thread_func(void* ptr);

ChunkManager::ChunkManager() : worldGenerator(WorldGenerator()), chunkMap(game_world.chunk_map)
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
	int i = 0;

	Camera playercam = game_world.player.get_camera();

	int player_x = playercam.get_pos().x / X_CHUNK_SIZE;
	if (playercam.get_pos().x < 0)
	{
		--player_x;
	}
	int player_y = playercam.get_pos().y / X_CHUNK_SIZE;
	if (playercam.get_pos().y < 0)
	{
		--player_y;
	}
	int player_z = playercam.get_pos().z / X_CHUNK_SIZE;
	if (playercam.get_pos().z < 0)
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
				if (search == chunkMap.end())
				{
					create_chunk(n, m, k);
					goto endloop;
				}
			}
		}
	}
	endloop:
	;
}

DWORD WINAPI create_chunk_thread_func(void* ptr)
{
	PackageChunkManagerXYZ* pointer = (PackageChunkManagerXYZ*)ptr;
	pointer->ptr_chunk_manager->create_chunk(pointer->x, pointer->y, pointer->z);

	return 0;
}

void ChunkManager::unload_chunk(Chunk* chunk, const Chunk3DPos pos)
{
	chunkMap.erase(pos);
	delete chunk;
}








///GAMMAL LOOP //////////////////////////////////////////////////////////////////////////////////////////////
//void ChunkManager::loop()
//{
//	PackageChunkManagerXYZ* pDataArray[MAX_CHUNK_THREADS];
//	DWORD   dwThreadIdArray[MAX_CHUNK_THREADS];
//	HANDLE  hThreadArray[MAX_CHUNK_THREADS];
//	int i = 0;
//
//	Camera playercam = game_world.player.get_camera();
//
//	int player_x = playercam.get_pos().x / X_CHUNK_SIZE;
//	if (playercam.get_pos().x < 0)
//	{
//		--player_x;
//	}
//	int player_y = playercam.get_pos().y / X_CHUNK_SIZE;
//	if (playercam.get_pos().y < 0)
//	{
//		--player_y;
//	}
//	int player_z = playercam.get_pos().z / X_CHUNK_SIZE;
//	if (playercam.get_pos().z < 0)
//	{
//		--player_z;
//	}
//
//	int lower_bound_x = player_x - RENDER_DISTANCE_CHUNK;
//	int higher_bound_x = player_x + RENDER_DISTANCE_CHUNK;
//	int lower_bound_y = player_y - RENDER_DISTANCE_CHUNK;
//	int higher_bound_y = player_y + RENDER_DISTANCE_CHUNK;
//	int lower_bound_z = player_z - RENDER_DISTANCE_CHUNK;
//	int higher_bound_z = player_z + RENDER_DISTANCE_CHUNK;
//
//	for (int n = lower_bound_x; n <= higher_bound_x; ++n)
//	{
//		for (int m = lower_bound_y; m <= higher_bound_y; ++m)
//		{
//			for (int k = lower_bound_z; k <= higher_bound_z; ++k)
//			{
//				auto search = chunkMap.find(Chunk3DPos(n, m, k));
//				if (search != chunkMap.end())
//				{
//					//std::cout << "Found chunk " << search->first.x << " " << search->first.y << " " << search->first.z << "       " << search->second << '\n';
//				}
//				else
//				{
//					//std::cout << "Not found, creating chunk\n";
//					pDataArray[i] = (PackageChunkManagerXYZ*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PackageChunkManagerXYZ));
//
//					if (pDataArray[i] == NULL)
//					{
//						// If the array allocation fails, the system is out of memory
//						// so there is no point in trying to print an error message.
//						// Just terminate execution.
//						ExitProcess(2);
//					}
//					pDataArray[i]->ptr_chunk_manager = this;
//					pDataArray[i]->x = n;
//					pDataArray[i]->y = m;
//					pDataArray[i]->z = k;
//
//
//					// Create the thread to begin execution on its own.
//
//					hThreadArray[i] = CreateThread(
//						NULL,                   // default security attributes
//						0,                      // use default stack size  
//						create_chunk_thread_func,       // thread function name
//						pDataArray[i],          // argument to thread function 
//						0,                      // use default creation flags 
//						&dwThreadIdArray[i]);   // returns the thread identifier 
//
//
//												// Check the return value for success.
//												// If CreateThread fails, terminate execution. 
//												// This will automatically clean up threads and memory. 
//
//					if (hThreadArray[i] == NULL)
//					{
//						ErrorHandler(TEXT("CreateThread"));
//						ExitProcess(3);
//					}
//
//					++i;
//
//					if (i == MAX_CHUNK_THREADS)
//					{
//						goto endloop;
//					}
//				}
//
//				///std::cout << "Player: " << player_x << " " << player_y << " " << player_z << "\n";
//			}
//		}
//	}
//endloop:
//
//	// Wait until all threads have terminated.
//
//	WaitForMultipleObjects(i, hThreadArray, TRUE, INFINITE);
//
//	// Close all thread handles and free memory allocations.
//
//	for (int j = 0; j<i; j++)
//	{
//		CloseHandle(hThreadArray[j]);
//		if (pDataArray[j] != NULL)
//		{
//			HeapFree(GetProcessHeap(), 0, pDataArray[j]);
//			pDataArray[j] = NULL;    // Ensure address is not reused.
//		}
//	}
//}