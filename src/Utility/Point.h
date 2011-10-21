#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Point(double x, double y, double z)
	{
		Point::x = x;
		Point::y = y;
		Point::z = z;
	}

	inline void setX(double x)
	{
		Point::x = x;
	}

	inline void setY(double y)
	{
		Point::y = y;
	}

	inline void setZ(double z)
	{
		Point::z = z;
	}

	inline double getX()
	{
		return x;
	}

	inline double getY()
	{
		return y;
	}

	inline double getZ()
	{
		return z;
	}

protected:
	double x, y, z;
};

#endif // POINT_H
