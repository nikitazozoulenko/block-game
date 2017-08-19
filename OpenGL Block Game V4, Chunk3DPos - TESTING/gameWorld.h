#ifndef BLOCK_GAME_GAME_WORLD_H
#define BLOCK_GAME_GAME_WORLD_H

#include <map>
#include "player.h"
#include "light.h"

//include eller forward declare de här 2?
#include "Chunk.h"
#include"Chunk3DPos.h"

typedef std::map<const Chunk3DPos, Chunk*> ChunkMap;
typedef std::pair<const Chunk3DPos, Chunk*> ChunkAndPosPair;

class GameWorld
{
public:
	GameWorld();

	Player player;
	ChunkMap chunk_map;
	Light sun;
	//std::vector<Light> lights;

protected:
private:
	//std::vector<Light> lights;
};

#endif // !BLOCK_GAME_GAME_WORLD_H
