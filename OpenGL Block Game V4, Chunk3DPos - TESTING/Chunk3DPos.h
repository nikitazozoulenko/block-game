#ifndef CHUNK3DPOS_H
#define CHUNK3DPOS_H

class Camera;

class Chunk3DPos
{
public:

	Chunk3DPos(const int& const x, const int& const y, const int& const z);
	friend bool operator<(const Chunk3DPos& firstVector, const Chunk3DPos& otherVector);

	int x;
	int y;
	int z;

protected:
private:
};

#endif // !CHUNK3DPOS_H