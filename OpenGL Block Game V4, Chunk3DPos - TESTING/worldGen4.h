#ifndef WORLD_GEN_FOUR_H
#define WORLD_GEN_FOUR_H

struct Chunk;

#include <glm\glm.hpp>

class WorldGenerator
{
public:
	WorldGenerator();

	Chunk* gen_chunk_at_pos(int chunkX, int chunkZ);
	float inline simplex_noise(float x, float z);
protected:
private:

	int weight_x;
	int weight_z;
	int weightFinal;
	float SIMPLEX_WEIGHT;

	static glm::vec2 unit_squared_vectors[4];

	int inline gen_seed_from_pos(int& posX, int& posZ);
	glm::vec2 CreateRandomGridVector(int posX, int posZ);

};


#endif // !WORLD_GEN_FOUR_H