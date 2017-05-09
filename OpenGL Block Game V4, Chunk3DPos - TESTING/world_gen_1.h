//#ifndef WORLD_GEN_ONE_H
//#define WORLD_GEN_ONE_H
//
//#include <glm\glm.hpp>
//#include "vector2D.h"
//#include "chunkV1.h"
//
//class WorldGeneratorV1 
//{
//public:
//	WorldGeneratorV1();
//
//	void inline Normalize(glm::vec2& my2DVector);
//	float inline lerp(float a0, float a1, float w);
//	Chunk* GenChunkAtPosition(Vector2D<int>& position);
//protected:
//private:
//	const int weightX;
//	const int weightY;
//	const int weightFinal;
//	const float PERLIN_WEIGHT;
//
//	glm::vec2 grid00;
//	glm::vec2 grid10;
//	glm::vec2 grid01;
//	glm::vec2 grid11;
//
//	int inline GenSeedFromWorldPos(int& posX, int& posY);
//	glm::vec2 CreateRandomGridVector(int posX, int posY);
//	int inline Perlin(float x, float z);
//};
//
//#endif // !WORLD_GEN_ONE_H