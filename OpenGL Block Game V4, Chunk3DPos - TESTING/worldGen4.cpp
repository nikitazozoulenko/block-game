#include "worldGen4.h"

#include <cstdlib>
#include <iostream>
#include "math.h"
#include "chunk.h"

glm::vec2 WorldGenerator::unit_squared_vectors[4] = { glm::vec2(1,1), glm::vec2(-1,1),  glm::vec2(1,-1),  glm::vec2(-1,-1) };

WorldGenerator::WorldGenerator() : weight_x(5), weight_z(3167), weightFinal(7919), SIMPLEX_WEIGHT(7)
{

}

int WorldGenerator::gen_seed_from_pos(int& posX, int& posZ)
{
	//calculate seed from 2 weights
	return ((posX * weight_x +  + posZ)*weight_z) % weightFinal;
}

glm::vec2 WorldGenerator::CreateRandomGridVector(int posX, int posZ)
{
	srand(gen_seed_from_pos(posX, posZ));

	glm::vec2 my2DVector = unit_squared_vectors[rand() % 4];
	return my2DVector;

}

static double dot(glm::vec2 g, double x, double z) {
	return g[0] * x + g[1] * z;
}

float WorldGenerator::simplex_noise(float x_in, float z_in)
{
	//Noise contribution from the three (N+1) corners
	float n0, n1, n2;

	//Skew the input space to determine simplex cell

	const float F2 = 0.5*(sqrt(3.0) - 1.0);
	float s = (x_in + z_in) * F2; // "Hairy Factor"
	int i = floorFloat(x_in + s);
	int j = floorFloat(z_in + s);

	const float G2 = (3.0 - sqrt(3.0)) / 6.0;
	float t = (i + j)*G2;
	float X0 = i - t; //Unskew the cell origin back to (x,y) space
	float Z0 = j - t;
	float x0 = x_in - X0;
	float z0 = z_in - Z0;

	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
	if (x0>z0) 
	{ 
		i1 = 1; 
		j1 = 0; 
	} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
	else 
	{ 
		i1 = 0; 
		j1 = 1; 
	} // upper triangle, YX order: (0,0)->(0,1)->(1,1)
	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6

	double x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
	double z1 = z0 - j1 + G2;
	double x2 = x0 - 1.0 + 2*G2; // Offsets for last corner in (x,y) unskewed coords
	double z2 = z0 - 1.0 + 2*G2;

	// Work out the hashed gradient vectors of the four simplex corners
	glm::vec2 gi0 = CreateRandomGridVector(i, j);
	glm::vec2 gi1 = CreateRandomGridVector(i + i1, j + j1);
	glm::vec2 gi2 = CreateRandomGridVector(i + 1, j + 1);


	 /*Calculate the contribution from the three corners*/
	double t0 = 0.5 - x0*x0 - z0*z0;
	if (t0<0) n0 = 0.0;
	else {
		t0 *= t0;
		n0 = t0 * t0 * dot(gi0, x0, z0);  // (x,y) of grad3 used for 2D gradient
	}
	double t1 = 0.5 - x1*x1 - z1*z1;
	if (t1<0) n1 = 0.0;
	else {
		t1 *= t1;
		n1 = t1 * t1 * dot(gi1, x1, z1);
	}
	double t2 = 0.5 - x2*x2 - z2*z2;
	if (t2<0) n2 = 0.0;
	else {
		t2 *= t2;
		n2 = t2 * t2 * dot(gi2, x2, z2);
	}
	// Add contributions from each corner to get the final noise value.
	// The result is scaled to return values in the interval [0,2].
	return (70.0 * (n0 + n1 + n2) + 1)*SIMPLEX_WEIGHT;
}

Chunk* WorldGenerator::gen_chunk_at_pos(int chunkX, int chunkZ)
{
	Chunk* chunk = new Chunk();

	for (int z = 0; z != Z_CHUNK_SIZE; ++z)
	{
		for (int x = 0; x != X_CHUNK_SIZE; ++x)
		{
			int y = simplex_noise(chunkX + static_cast<float>(x) / X_CHUNK_SIZE, chunkZ + static_cast<float>(z) / Z_CHUNK_SIZE) + 0.5;
			chunk->blockArray[x + z*X_CHUNK_SIZE + y*X_CHUNK_SIZE*Z_CHUNK_SIZE] = 1;
			for (int i = y - 1; i > -1; --i)
			{
				chunk->blockArray[x + z*X_CHUNK_SIZE + i*X_CHUNK_SIZE*Z_CHUNK_SIZE] = 1;
			}
			for (int i = y + 1; i < Y_CHUNK_SIZE; ++i)
			{
				chunk->blockArray[x + z*X_CHUNK_SIZE + i*X_CHUNK_SIZE*Z_CHUNK_SIZE] = 0;
			}
		}
	}

	return chunk;

	//REMEMBER: DELETE STUFF INSIDE CHUNK????
}