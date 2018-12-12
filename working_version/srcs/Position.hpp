#ifndef POSITION_HPP
#define POSITION_HPP

struct Pos2D{
	Pos2D()
	{
	}

	Pos2D operator=(const Pos2D & rhs)
	{
	    x = rhs.x;
	    y = rhs.y;
	    return *this;
	}

	int x;
	int y;
};

struct PosF2D{
	float x;
	float y;
};

struct Pos3D{
	int x;
	int y;
	int z;
};

#endif