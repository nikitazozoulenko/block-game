//#include "world_gen_1.h"
//
//#include <cstdlib>
//#include <iostream>
//
//int numbers2[10] = { 0,0,0,0,0,0,0,0,0,0 };
//glm::vec2 unitSquareVectors[] = { glm::vec2(-1,-1), glm::vec2(-1,1), glm::vec2(1,-1) , glm::vec2(1,1)};
//
//WorldGeneratorV1::WorldGeneratorV1() : weightX(5), weightY(2153), weightFinal(7919), PERLIN_WEIGHT(40) { }
//
//int WorldGeneratorV1::GenSeedFromWorldPos(int& posX, int& posY)
//{
//	///IMPLEMENT ERROR CORRECTION FOR BIG SEEDS
//	//
//
//	//
//
//	//calculate seed from 2 weights
//	//return (weightX*posX + weightY*posY) % weightFinal;
//	return (((posX * weightX + posY) * weightY) % weightFinal);
//}
//
//void WorldGeneratorV1::Normalize(glm::vec2& my2DVector)
//{
//	float length = sqrt(my2DVector.x * my2DVector.x + my2DVector.y * my2DVector.y);
//	my2DVector.x /= length;
//	my2DVector.y /= length;
//}
//
//glm::vec2 WorldGeneratorV1::CreateRandomGridVector(int posX, int posY)
//{
//	srand(GenSeedFromWorldPos(posX, posY));
//
//	/*glm::vec2 my2DVector(rand(), rand());
//	Normalize(my2DVector);*/
//
//	glm::vec2 my2DVector = unitSquareVectors[rand() % 4];
//	return my2DVector;
//}
//
//float WorldGeneratorV1::lerp(float a0, float a1, float w)
//{
//	return a0*(1-w)+a1*w;
//}
//
//int WorldGeneratorV1::Perlin(float x, float z)
//{
//	//interpolation weights
//	//could use other functions
//	float sx = x;
//	float sz = z;
//
//	//interpolate between grid point gradients
//	float dot00 = x*grid00.x + z*grid00.y;
//	float dot10 = (x-1)*grid10.x + z*grid10.y;
//	float dot01 = x*grid01.x + (z-1)*grid01.y;
//	float dot11 = (x-1)*grid11.x + (z-1)*grid11.y;
//
//	float n0 = lerp(dot00, dot10, sx);
//	float n1 = lerp(dot01, dot11, sx);
//
//	return static_cast<int>(PERLIN_WEIGHT * lerp(n0, n1, sz)+ PERLIN_WEIGHT +0.5);
//}
//
//Chunk* WorldGeneratorV1::GenChunkAtPosition(Vector2D<int>& position)
//{
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
//			for (int y = Perlin(static_cast<float>(x) / X_CHUNK_SIZE, static_cast<float>(z) / Z_CHUNK_SIZE); y != -1; --y) {
//				chunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] = 1;
//			}
//		}
//	}
//	//grid00.x *= 10;
//	//numbers2[(int)grid00.x]++;
//	//grid10.x *= 10;
//	//numbers2[(int)grid10.x]++;
//	//grid01.x *= 10;
//	//numbers2[(int)grid01.x]++;
//	//grid11.x *= 10;
//	//numbers2[(int)grid11.x]++;
//
//	//for (int i = 0; i != 10; ++i)
//	//{
//	//	std::cout << numbers2[i] << "\t";
//	//}
//	//std::cout << std::endl;
//
//	return chunk;
//
//	//REMEMBER: DELETE STUFF INSIDE CHUNK????
//}