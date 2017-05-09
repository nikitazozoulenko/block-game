#ifndef CHUNK3DPOS_H
#define CHUNK3DPOS_H

class Camera;

class Chunk3DPos
{
public:

	Chunk3DPos(int& x, int& y, int& z);
	friend bool operator<(const Chunk3DPos& firstVector, const Chunk3DPos& otherVector);
	static void UpdateCamera(Camera& camera);

	int x;
	int y;
	int z;

protected:
private:
	static Camera& camera;
};

#endif // !CHUNK3DPOS_H