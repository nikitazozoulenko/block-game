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
	ChunkManager(const Camera& const camera);
	void create_chunk(const int x, const int y, const int z);
	inline ChunkMap& GetChunkMap() { return chunkMap; }
protected:
private:
	Chunk* init_chunk(Chunk* const chunk, const Chunk3DPos& const position);
	WorldGenerator worldGenerator;
	static Camera& camera;
	ChunkMap chunkMap;

	static void InitStaticCamera(const Camera& const camera);
};

#endif // !CHUNKMANAGER_H
