#include "Vector2.h"

Vector2::Vector2()
{
	X = 0.0;
	Y = 0.0;
	Length = 0.0;
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
	Length = 0;
}

const float Vector2::setLength()
{
	return sqrt(X * X + Y * Y);
}

const float Vector2::getLengt()
{
	return sqrt(X * X + Y * Y);
}

const float Vector2::GetX()
{
	return X;
}

const float Vector2::GetY()
{
	return Y;
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
	// Prevent self assignment. Two objects
	// are equal if their memory address are equal.
	if (this == &rhs)
	{
		return *this;
	}

	X = rhs.X;
	Y = rhs.Y;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	X = X + rhs.X;
	Y = Y + rhs.Y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	X = X - rhs.X;
	Y = Y - rhs.Y;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
	X = X * rhs.X;
	Y = Y * rhs.Y;

	return *this;
}

Vector2& Vector2::operator/=(const Vector2& rhs)
{
	X = X / rhs.X;
	Y = Y / rhs.Y;

	return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs)
{
	Vector2 sum;

	sum.X = X + rhs.X;
	sum.Y = Y + rhs.Y;

	return sum;
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
	Vector2 sub;
	sub.X = X - rhs.X;
	sub.Y = Y - rhs.Y;

	return sub;
}

Vector2 Vector2::operator-()
{
	return Vector2(-X, -Y);
}

Vector2 Vector2::operator*(const Vector2& rhs)
{
	Vector2 scaled;

	scaled.Y = Y * rhs.Y;
	scaled.X = X * rhs.X;

	return scaled;
}

Vector2 Vector2::operator/(const Vector2& rhs)
{
	Vector2 inverseScaled;

	inverseScaled.X = X / rhs.X;
	inverseScaled.Y = Y / rhs.Y;

	return inverseScaled;
}

bool Vector2::operator==(const Vector2& rhs)
{
	return
		X == rhs.X &&
		Y == rhs.Y;
}

bool Vector2::operator!=(const Vector2& rhs)
{
	return
		X != rhs.X ||
		Y != rhs.Y;
}

// friend functions
Vector2 operator*(float scaleUnit, const Vector2& rhs)
{
	Vector2 scaled;
	scaled.X = scaleUnit * rhs.X;
	scaled.Y = scaleUnit * rhs.Y;

	return scaled;
}

Vector2 operator*(const Vector2& lhs, float scaleUnit)
{
	Vector2 scaled;
	scaled.X = scaleUnit * lhs.X;
	scaled.Y = scaleUnit * lhs.Y;

	return scaled;
}