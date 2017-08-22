#ifndef BLOCK_GAME_GAME_WORLD_H
#define BLOCK_GAME_GAME_WORLD_H

#include <map>
#include "player.h"
#include "light.h"

//include eller forward declare de här 2?
#include "chunk.h"
#include "position2D.h"

typedef std::map<const Position2D, Chunk*> ChunkMap;
typedef std::pair<const Position2D, Chunk*> ChunkAndPosPair;

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
