#pragma once

#include <cmath>

class Vector2Int
{
public:
	int x, y; // coordinates
	Vector2Int(int xArg = 0, int yArg = 0) : x(xArg), y(yArg) {} // default constructor
	
	// methods
	void invert()
	{
		x = -x;
		y = -y;
	}
	float magnitude() { return sqrt(x*x + y*y); }
	int sqrMagnitude() { return x*x + y*y; }
	
	// OPERATORS
	// scalar multiplication
	void operator*= (int scalar)
	{
		x *= scalar;
		y *= scalar;
	}
	Vector2Int operator* (int scalar) const
	{
		return Vector2Int(x * scalar, y * scalar);
	}
	// addition
	void operator+= (const Vector2Int& vect)
	{
		x += vect.x;
		y += vect.y;
	}
	Vector2Int operator+ (const Vector2Int& vect) const
	{
		return Vector2Int(x + vect.x, y + vect.y);
	}
	// substraction
	void operator-= (const Vector2Int& vect)
	{
		x -= vect.x;
		y -= vect.y;
	}
	Vector2Int operator- (const Vector2Int& vect) const
	{
		return Vector2Int(x - vect.x, y - vect.y);
	}
	Vector2Int operator- () const
	{
		return Vector2Int(-x, -y);
	}
	// multiplication
	Vector2Int componentProduct(const Vector2Int vect) const
	{
		return Vector2Int(x * vect.x, y * vect.y);
	}
	// scalar product
	int scalarProduct (const Vector2Int vect) const
	{
		return x*vect.x + y*vect.y;
	}
	int operator* (const Vector2Int vect) const
	{
		return x*vect.x + y*vect.y;
	}
	// vector product
	Vector2Int vectorProduct(const Vector2Int vect) const
	{
		return Vector2Int(
			y*vect.x - x*vect.y,
			x*vect.y - y*vect.x
		);
	}
	Vector2Int operator% (const Vector2Int vect) const
	{
		return Vector2Int(
			y*vect.x - x*vect.y,
			x*vect.y - y*vect.x
		);
	}
	void operator%= (const Vector2Int vect)
	{
		x = y*vect.x - x*vect.y;
		y = x*vect.y - y*vect.x;
	}
	void zero()
	{
		this->x = 0;
		this->y = 0;
	}
};