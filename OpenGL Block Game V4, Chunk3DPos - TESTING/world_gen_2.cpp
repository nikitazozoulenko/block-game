//#include "world_gen_2.h"
//
//#include <cstdlib>
//#include <iostream>
//#include "math.h"
//
//glm::vec3 WorldGeneratorV2::unitSquareVectors[8] = { glm::vec3(1,1,1), glm::vec3(-1,1,1),  glm::vec3(1,-1,1),  glm::vec3(1,1,-1),
//													glm::vec3(-1,-1,1),  glm::vec3(1,-1,-1),  glm::vec3(-1,1,-1),  glm::vec3(-1,-1,-1) };
//
//WorldGeneratorV2::WorldGeneratorV2() : weightX(5), weightY(991), weightZ(3167), weightFinal(7919), PERLIN_WEIGHT(40)
//{ 
//
//}
//
//int WorldGeneratorV2::GenSeedFromWorldPos(int& posX, int& posY, int& posZ)
//{
//	//calculate seed from 2 weights
//	return ((((posX * weightX + posY) * weightY) +posZ)*weightZ) % weightFinal;
//}
//
//
//glm::vec3 WorldGeneratorV2::CreateRandomGridVector(int posX, int posY, int posZ)
//{
//	srand(GenSeedFromWorldPos(posX, posY, posZ));
//
//	glm::vec3 my3DVector = unitSquareVectors[rand() % 8];
//	return my3DVector;
//
//	return my3DVector;
//}
//
//static double dot(glm::vec3 g, double x, double y, double z) {
//	return g[0] * x + g[1] * y + g[2] * z;
//}
//
//float WorldGeneratorV2::SimplexNoise(float x_in, float y_in, float z_in)
//{
//	//Noise contribution from the four (N+1) corners
//	float n0, n1, n2, n3;
//
//	//Skew the input space to determine simplex cell
//	const float F3 = 1.0f / 3.0f;
//	float s = (x_in + y_in + z_in) * F3; // "Hairy Factor"
//	int i = floorFloat(x_in + s);
//	int j = floorFloat(y_in + s);
//	int k = floorFloat(z_in + s);
//
//	const float G3 = 1.0f / 6.0f;
//	float t = (i + j + k)*G3;
//	float X0 = i - t; //Unskew the cell origin back to (x,y) space
//	float Y0 = j - t;
//	float Z0 = k - t;
//	float x0 = x_in - X0;
//	float y0 = y_in - Y0;
//	float z0 = z_in - Z0;
//
//	// For the 3D case, the simplex shape is a slightly irregular tetrahedron.
//	// Determine which simplex we are in.
//	int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
//	int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
//	if (x0 >= y0) {
//		if (y0 >= z0)
//		{
//			i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
//		} // X Y Z order
//		else if (x0 >= z0) { i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1; } // X Z Y order
//		else { i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1; } // Z X Y order
//	}
//	else // x0<y0
//	{ 
//		if (y0<z0) 
//		{ 
//			i1 = 0; 
//			j1 = 0; 
//			k1 = 1; 
//			i2 = 0; 
//			j2 = 1; 
//			k2 = 1; 
//		} // Z Y X order
//		else if (x0<z0) 
//		{ 
//			i1 = 0; 
//			j1 = 1; 
//			k1 = 0; 
//			i2 = 0; 
//			j2 = 1; 
//			k2 = 1; 
//		} // Y Z X order
//		else 
//		{ 
//			i1 = 0; 
//			j1 = 1; 
//			k1 = 0; 
//			i2 = 1; 
//			j2 = 1; 
//			k2 = 0; 
//		} // Y X Z order
//	}
//	// A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
//	// a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
//	// a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
//	// c = 1/6.
//
//	double x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
//	double y1 = y0 - j1 + G3;
//	double z1 = z0 - k1 + G3;
//	double x2 = x0 - i2 + 2.0*G3; // Offsets for third corner in (x,y,z) coords
//	double y2 = y0 - j2 + 2.0*G3;
//	double z2 = z0 - k2 + 2.0*G3;
//	double x3 = x0 - 1.0 + 3.0*G3; // Offsets for last corner in (x,y,z) coords
//	double y3 = y0 - 1.0 + 3.0*G3;
//	double z3 = z0 - 1.0 + 3.0*G3;
//
//
//	// Work out the hashed gradient vectors of the four simplex corners
//	///////*glm::vec3 gi0 = CreateRandomGridVector(i, j, k);
//	//////glm::vec3 gi1 = CreateRandomGridVector(i+i1, j+j1, k+k1);
//	//////glm::vec3 gi2 = CreateRandomGridVector(i+i2, j+j2, k+k2);
//	//////glm::vec3 gi3 = CreateRandomGridVector(i+1, j+1, k+1);*/
//
//	glm::vec3 gi0 = CreateRandomGridVector(i, j, k);
//	glm::vec3 gi1 = CreateRandomGridVector(i+i1, j+j1, k+k1);
//	glm::vec3 gi2 = CreateRandomGridVector(i+i2, j+j2, k+k2);
//	glm::vec3 gi3 = CreateRandomGridVector(i+1, j+1, k+1);
//
//	// Calculate the contribution from the four corners
//	double t0 = 0.5 - x0*x0 - y0*y0 - z0*z0;
//	if (t0<0) n0 = 0.0;
//	else {
//		t0 *= t0;
//		n0 = t0 * t0 * dot(gi0, x0, y0, z0);
//	}
//	double t1 = 0.5 - x1*x1 - y1*y1 - z1*z1;
//	if (t1<0) n1 = 0.0;
//	else {
//		t1 *= t1;
//		n1 = t1 * t1 * dot(gi1, x1, y1, z1);
//	}
//	double t2 = 0.5 - x2*x2 - y2*y2 - z2*z2;
//	if (t2<0) n2 = 0.0;
//	else {
//		t2 *= t2;
//		n2 = t2 * t2 * dot(gi2, x2, y2, z2);
//	}
//	double t3 = 0.5 - x3*x3 - y3*y3 - z3*z3;
//	if (t3<0) n3 = 0.0;
//	else {
//		t3 *= t3;
//		n3 = t3 * t3 * dot(gi3, x3, y3, z3);
//	}
//
//	// Add contributions from each corner to get the final noise value.
//	// The result is scaled to stay just inside [-1,1]
//	return 32.0*(n0 + n1 + n2 + n3);
//}
//
//Chunk* WorldGeneratorV2::GenChunkAtPosition(Vector2D<int>& position)
//{
//	Chunk* chunk = new Chunk();
//
//	for (int z = 0; z != Z_CHUNK_SIZE; ++z)
//	{
//		for (int x = 0; x != X_CHUNK_SIZE; ++x)
//		{
//			for (int y = 0; y != Y_CHUNK_SIZE; ++y)
//			{
//				if (SimplexNoise(position.x + static_cast<float>(x) / X_CHUNK_SIZE, static_cast<float>(y) / Y_CHUNK_SIZE, position.y + static_cast<float>(z) / Z_CHUNK_SIZE) < -0.1)
//				{
//					chunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] = 1;
//				}
//			}
//		}
//	}
//
//	return chunk;
//
//	//REMEMBER: DELETE STUFF INSIDE CHUNK????
//}