#include "Chunk3DPos.h"
#include "camera.h"

Chunk3DPos::Chunk3DPos(const int& const x, const int& const y, const int& const z) : x(x), y(y), z(z) { }


bool operator<(const Chunk3DPos & firstVector, const Chunk3DPos & otherVector)
{
	int x1 = firstVector.x;
	int y1 = firstVector.y;
	int z1 = firstVector.z;

	int d1 = x1*x1 + y1*y1 + z1*z1;

	int x2 = otherVector.x;
	int y2 = otherVector.y;
	int z2 = otherVector.z;

	int d2 = x2*x2 + y2*y2 + z2*z2;

	//compare distances:
	if (d1 < d2)
	{
		return true;
	}
	if (d2 < d1)
	{
		return false;
	}

	//if the distances are the same:
	if (x1 < x2)
	{
		return true;
	}
	if (x2 < x1)
	{
		return false;
	}
	if (y1 < y2)
	{
		return true;
	}
	if (y2 < y1)
	{
		return false;
	}
	if (z1 < z2)
	{
		return true;
	}
	return false;
}