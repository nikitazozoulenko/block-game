#ifndef CHUNKMANAGER_BLOCK_GAME_H
#define CHUNKMANAGER_BLOCK_GAME_H

#include "worldGen4.h"
#include "gameWorld.h"

class ChunkManager
{
public:
	ChunkManager();
	void create_chunk(const int x, const int z);
	void create_chunk(const glm::vec2 pos);
	void unload_chunk(Chunk* chunk, Position2D pos);
	inline ChunkMap& GetChunkMap() { return chunkMap; }
	void ChunkManager::loop();
protected:
private:
	void search_and_create_chunk(int x, int z);
	Chunk* init_chunk(Chunk* const chunk, const Position2D& const position);
	WorldGenerator worldGenerator;
	ChunkMap& chunkMap;
};

struct PackageChunkManagerInt
{
	ChunkManager* ptr_chunk_manager;
	int i;
};
#endif // !CHUNKMANAGER_BLOCK_GAME_H
