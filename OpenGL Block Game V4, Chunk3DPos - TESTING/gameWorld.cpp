#include "gameWorld.h"

GameWorld::GameWorld() : player(Player(glm::vec3(0, 0, 0), 0, 0, 0)), chunk_map(ChunkMap()), sun(Light(glm::vec3(10000000, 20000000, 5000000)))
{
	
}

void GameWorld::test_function()
{

}