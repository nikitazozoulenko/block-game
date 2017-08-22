#include "position2D.h"

Position2D::Position2D(const int& const x, const int& const z) : x(x), z(z) { }


bool operator<(const Position2D & firstVector, const Position2D & otherVector)
{
	int x1 = firstVector.x;
	int z1 = firstVector.z;

	int d1 = x1*x1 + z1*z1;

	int x2 = otherVector.x;
	int z2 = otherVector.z;

	int d2 = x2*x2 + z2*z2;

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
	if (z1 < z2)
	{
		return true;
	}
	return false;
}