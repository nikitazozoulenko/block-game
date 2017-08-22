#ifndef TWO_D_POSITION_H
#define TWO_D_POSITION_H

class Position2D
{
public:

	Position2D(const int& const x, const int& const z);
	friend bool operator<(const Position2D& firstVector, const Position2D& otherVector);

	int x;
	int z;

protected:
private:
};

#endif // !TWO_D_POSITION_H