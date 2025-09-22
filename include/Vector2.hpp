#pragma once

#include <cmath>

class Vector2
{
public:
	float x, y; // coordinates
	Vector2(float xArg = 0, float yArg = 0) : x(xArg), y(yArg) {} // default constructor
	
	// methods
	void invert()
	{
		x = -x;
		y = -y;
	}
	float magnitude() { return sqrt(x*x + y*y); }
	float sqrMagnitude() { return x*x + y*y; }
	Vector2 norm()
	{
		Vector2 returnVect = *this;
		float len = magnitude();
		if (len > 0)
			returnVect *= 1 / len;
			
		return returnVect;
	}
	
	// OPERATORS
	// scalar multiplication
	void operator*= (float scalar)
	{
		x *= scalar;
		y *= scalar;
	}
	Vector2 operator* (float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}
	// addition
	void operator+= (const Vector2& vect)
	{
		x += vect.x;
		y += vect.y;
	}
	Vector2 operator+ (const Vector2& vect) const
	{
		return Vector2(x + vect.x, y + vect.y);
	}
	// substraction
	void operator-= (const Vector2& vect)
	{
		x -= vect.x;
		y -= vect.y;
	}
	Vector2 operator- (const Vector2& vect) const
	{
		return Vector2(x - vect.x, y - vect.y);
	}
	Vector2 operator- () const
	{
		return Vector2(-x, -y);
	}
	// multiplication
	Vector2 componentProduct(const Vector2 vect) const
	{
		return Vector2(x * vect.x, y * vect.y);
	}
	// scalar product
	float scalarProduct (const Vector2 vect) const
	{
		return x*vect.x + y*vect.y;
	}
	float operator* (const Vector2 vect) const
	{
		return x*vect.x + y*vect.y;
	}
	// vector product
	Vector2 vectorProduct(const Vector2 vect) const
	{
		return Vector2(
			y*vect.x - x*vect.y,
			x*vect.y - y*vect.x
		);
	}
	Vector2 operator% (const Vector2 vect) const
	{
		return Vector2(
			y*vect.x - x*vect.y,
			x*vect.y - y*vect.x
		);
	}
	void operator%= (const Vector2 vect)
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