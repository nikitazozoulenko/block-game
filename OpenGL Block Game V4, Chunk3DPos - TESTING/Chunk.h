#ifndef CHUNKV2_H
#define CHUNKV2_H

#define X_CHUNK_SIZE 32
#define Y_CHUNK_SIZE 32
#define Z_CHUNK_SIZE 32

#include <glm\glm.hpp>

class Chunk
{
public:

	glm::ivec3* worldPositionArray;
	uint16_t blockArray[X_CHUNK_SIZE * Y_CHUNK_SIZE * Z_CHUNK_SIZE];
	int countRenderedBlocks;
	bool needsUpdating = true;

protected:
private:

};

#endif // !CHUNKV2_H
