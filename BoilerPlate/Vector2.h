#pragma once

#ifndef _VECTOR2_
#define _VECTOR2_

#include <cmath>

class Vector2
{
public: Vector2();
		explicit Vector2(float x, float y);
		const float GetX();
		const float GetY();
		const float setLength();
		const float getLengt();

		Vector2& operator=(const Vector2& rhs);
		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
		Vector2& operator*=(const Vector2& rhs);
		Vector2& operator/=(const Vector2& rhs);
		Vector2 operator+(const Vector2& rhs);
		Vector2 operator-(const Vector2& rhs);
		Vector2 operator-();
		Vector2 operator*(const Vector2& rhs);
		Vector2 operator/(const Vector2& rhs);
		bool operator==(const Vector2& rhs);
		bool operator!=(const Vector2& rhs);
		friend Vector2 operator*(float scaleUnit, const Vector2& rhs);
		friend Vector2 operator*(const Vector2& lhs, float scaleUnit);

private:   float X;
		   float Y;
		   float Length;
};
#endif // !_VECTOR2_