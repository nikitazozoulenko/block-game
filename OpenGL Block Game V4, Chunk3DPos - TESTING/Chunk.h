#ifndef CHUNKV2_H
#define CHUNKV2_H

#define X_CHUNK_SIZE 16
#define Y_CHUNK_SIZE 128
#define Z_CHUNK_SIZE 16

#include <glm\glm.hpp>

struct Chunk
{
public:

	enum Block{
		SOUTH,
		NORTH,
		DOWN,
		UP,
		WEST,
		EAST,

		NUM_DIRECTIONS
	};

	glm::ivec3* worldPositionArray[6];
	uint16_t blockArray[X_CHUNK_SIZE * Y_CHUNK_SIZE * Z_CHUNK_SIZE];
	int countRenderedBlocks[6];
	bool needsUpdating[6] = { true, true, true, true, true, true };

protected:
private:

};

#endif // !CHUNKV2_H
