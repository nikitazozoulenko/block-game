#ifndef CHUNKMANAGER_BLOCK_GAME_H
#define CHUNKMANAGER_BLOCK_GAME_H

#include "world_gen_3.h"
#include "gameWorld.h"

class ChunkManager
{
public:
	ChunkManager();
	void create_chunk(const int x, const int y, const int z);
	void unload_chunk(Chunk* chunk, Chunk3DPos pos);
	inline ChunkMap& GetChunkMap() { return chunkMap; }
	void ChunkManager::loop();
protected:
private:
	Chunk* init_chunk(Chunk* const chunk, const Chunk3DPos& const position);
	WorldGenerator worldGenerator;
	ChunkMap& chunkMap;
};

struct PackageChunkManagerXYZ
{
	ChunkManager* ptr_chunk_manager;
	int x;
	int y;
	int z;
};
#endif // !CHUNKMANAGER_BLOCK_GAME_H
