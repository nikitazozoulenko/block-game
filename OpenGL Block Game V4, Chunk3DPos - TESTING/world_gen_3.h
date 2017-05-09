#ifndef WORLD_GEN_THREE_H
#define WORLD_GEN_THREE_H

class Chunk;

#include <glm\glm.hpp>

class WorldGenerator
{
public:
	WorldGenerator();

	Chunk* GenChunkAtPosition(int chunkX, int chunkY, int chunkZ);
	float inline SimplexNoise(float x, float y, float z);
protected:
private:
	const int weightX;
	const int weightY;
	const int weightZ;
	const int weightFinal;
	const float PERLIN_WEIGHT;

	static glm::vec3 unitSquareVectors[8];

	int inline GenSeedFromWorldPos(int& posX, int& posY, int& posZ);
	glm::vec3 CreateRandomGridVector(int posX, int posY, int posZ);
	
};


#endif // !WORLD_GEN_THREE_H