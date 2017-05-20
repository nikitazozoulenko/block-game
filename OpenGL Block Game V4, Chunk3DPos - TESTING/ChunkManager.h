#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

class Camera;

#include <map>
#include <glm\glm.hpp>
#include "Chunk.h"
#include "Chunk3DPos.h"
#include "world_gen_3.h"
#include "camera.h"

typedef std::map<const Chunk3DPos, Chunk*> ChunkMap;
typedef std::pair<const Chunk3DPos, Chunk*> ChunkAndPosPair;

class ChunkManager
{
public:
	ChunkManager(Camera& const camera);
	void create_chunk(const int x, const int y, const int z);
	void unload_chunk(Chunk* chunk, Chunk3DPos pos);
	inline ChunkMap& GetChunkMap() { return chunkMap; }
	void ChunkManager::loop();
protected:
private:
	Chunk* init_chunk(Chunk* const chunk, const Chunk3DPos& const position);
	WorldGenerator worldGenerator;
	Camera& const camera;
	ChunkMap chunkMap;

	
};

#endif // !CHUNKMANAGER_H
