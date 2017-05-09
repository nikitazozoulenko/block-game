//#include "world_gen_0.h"
//
//#include <cstdlib>
//#include <iostream>
//
//WorldGeneratorV0::WorldGeneratorV0() : weightX(6719), weightY(11), PERLIN_WEIGHT(20) { }
//
//int WorldGeneratorV0::GenSeedFromWorldPos(int& posX, int& posY)
//{
//	///IMPLEMENT ERROR CORRECTION FOR BIG SEEDS
//	//
//
//	//
//
//	//calculate seed from 2 weights
//	return weightX*posX + weightY*posY;
//}
//
//void WorldGeneratorV0::Normalize(glm::vec2& my2DVector)
//{
//	float length = sqrt(my2DVector.x * my2DVector.x + my2DVector.y * my2DVector.y);
//	my2DVector.x /= length;
//	my2DVector.y /= length;
//}
//
//glm::vec2 WorldGeneratorV0::CreateRandomGridVector(int posX, int posY)
//{
//	srand(GenSeedFromWorldPos(posX, posY));
//
//	glm::vec2 my2DVector(rand(), rand());
//	Normalize(my2DVector);
//
//	return my2DVector;
//}
//
//float WorldGeneratorV0::lerp(float a0, float a1, float w)
//{
//	return a0*(1-w)+a1*w;
//}
//
//int WorldGeneratorV0::Noise(float x, float z)
//{
//	float n0 = lerp(grid00.x, grid10.x, x);
//	float n1 = lerp(grid01.x, grid11.x, x);
//
//	return static_cast<int>(PERLIN_WEIGHT*lerp(n1, n0, z)+PERLIN_WEIGHT);
//}
//
//Chunk* WorldGeneratorV0::GenChunkAtPosition(Vector2D<int>& position)
//{
//	std::cout << "Position: " << position.x << " " << position.y << std::endl;
//	std::cout << "seed00 " << GenSeedFromWorldPos(position.x, position.y) << std::endl;
//	int pos = position.x + 1;
//	std::cout << "seed10 " << GenSeedFromWorldPos(pos, position.y) << std::endl;
//
//	Chunk* chunk = new Chunk();
//
//	//grid vectors, gridxy, (x,y)
//	grid00 = CreateRandomGridVector(position.x, position.y);
//	grid10 = CreateRandomGridVector(position.x + 1, position.y);
//	grid01 = CreateRandomGridVector(position.x, position.y + 1);
//	grid11 = CreateRandomGridVector(position.x + 1, position.y + 1);
//
//	for (int z = 0; z != Z_CHUNK_SIZE; ++z)
//	{
//		for (int x = 0; x != X_CHUNK_SIZE; ++x)
//		{
//			chunk->blockArray[x + z*X_CHUNK_SIZE + Noise(static_cast<float>(x) / X_CHUNK_SIZE, static_cast<float>(z) / Z_CHUNK_SIZE)*X_CHUNK_SIZE*Z_CHUNK_SIZE] = 1;
//		}
//	}
//
//	return chunk;
//}