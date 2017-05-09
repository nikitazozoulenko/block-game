//#ifndef WORLD_GEN_TWO_H
//#define WORLD_GEN_TWO_H
//
//#include <glm\glm.hpp>
//#include "vector2D.h"
//#include "chunkV1.h"
//
//class WorldGeneratorV2
//{
//public:
//	WorldGeneratorV2();
//
//	Chunk* GenChunkAtPosition(Vector2D<int>& position);
//protected:
//private:
//	const int weightX;
//	const int weightY;
//	const int weightZ;
//	const int weightFinal;
//	const float PERLIN_WEIGHT;
//
//	static glm::vec3 unitSquareVectors[8];
//
//	int inline GenSeedFromWorldPos(int& posX, int& posY, int& posZ);
//	glm::vec3 CreateRandomGridVector(int posX, int posY, int posZ);
//	float inline SimplexNoise(float x, float y, float z);
//};
//
//#endif // !WORLD_GEN_TWO_H