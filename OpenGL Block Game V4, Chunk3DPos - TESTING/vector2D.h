#ifndef VECTOR2D_H
#define VECTOR2D_H

template <typename T> 
struct Vector2D
{
	Vector2D<T>(T x, T y) : x(x), y(y) {}
	friend bool operator<(const Vector2D& firstVector, const Vector2D& otherVector) 
	{ 
		if (firstVector.x < otherVector.x)
		{
			return true;
		}
		if (otherVector.x < firstVector.x)
		{
			return false;
		}
		if (firstVector.y < otherVector.y)
		{
			return true;
		}
		return false;
	}

	T x;
	T y;
};

#endif // !VECTOR2D_H
