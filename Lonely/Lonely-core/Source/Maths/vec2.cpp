#include "vec2.h"

namespace lonely { namespace maths {

	vec2::vec2()				 : x(0), y(0)			{}
	vec2::vec2(float x, float y) : x(x), y(y)			{}
	vec2::vec2(float scalar)	 : x(scalar), y(scalar) {}


	vec2 vec2::Normalize() const
	{
		float length = Magnitude();
		return vec2(x / length, y / length);
	}

	float vec2::Magnitude() const
	{
		return sqrt(x * x + y * y);
	}
	
	float vec2::Distance(const vec2& other) const
	{
		float X = x - other.x;
		float Y = y - other.y;
		return sqrt(X * X + Y * Y);
	}

	float vec2::Dot(const vec2& other) const
	{
		return x * other.x + y * other.y;
	}


	vec2& vec2::Add(const vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2& vec2::Substract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	vec2& vec2::Multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	vec2& vec2::Divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}


	vec2& vec2::Add(float value)
	{
		x += value;
		y += value;
		return *this;
	}

	vec2& vec2::Substract(float value)
	{
		x -= value;
		y -= value;
		return *this;
	}

	vec2& vec2::Multiply(float value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	vec2& vec2::Divide(float value)
	{
		x /= value;
		y /= value;
		return *this;
	}


	vec2 operator+(vec2 left, const vec2& right)
	{
		return left.Add(right);
	}

	vec2 operator-(vec2 left, const vec2& right)
	{
		return left.Substract(right);
	}
	
	vec2 operator*(vec2 left, const vec2& right)
	{
		return left.Multiply(right);
	}
	
	vec2 operator/(vec2 left, const vec2& right)
	{
		return left.Divide(right);
	}


	vec2 operator+(vec2 left, float value)
	{
		return vec2(left.x + value, left.y + value);
	}

	vec2 operator-(vec2 left, float value)
	{
		return vec2(left.x - value, left.y - value);
	}

	vec2 operator*(vec2 left, float value)
	{
		return vec2(left.x * value, left.y * value);
	}

	vec2 operator/(vec2 left, float value)
	{
		return vec2(left.x / value, left.y / value);
	}

	vec2 operator-(const vec2& value)
	{
		return vec2(-value.x, -value.y);
	}


	vec2& vec2::operator+=(const vec2& other)
	{
		return Add(other);
	}

	vec2& vec2::operator-=(const vec2& other)
	{
		return Substract(other);
	}

	vec2& vec2::operator*=(const vec2& other)
	{
		return Multiply(other);
	}

	vec2& vec2::operator/=(const vec2& other)
	{
		return Divide(other);
	}


	vec2& vec2::operator+=(float value)
	{
		return Add(value);
	}

	vec2& vec2::operator-=(float value)
	{
		return Substract(value);
	}

	vec2& vec2::operator*=(float value)
	{
		return Multiply(value);
	}

	vec2& vec2::operator/=(float value)
	{
		return Divide(value);
	}


	bool vec2::operator==(const vec2& other) const
	{
		
		return x == other.x && y == other.y;
	}

	bool vec2::operator!=(const vec2& other) const
	{
		return !(*this == other);
	}


	bool vec2::operator>(const vec2& other) const
	{
		return x > other.x && y > other.y;
	}

	bool vec2::operator<(const vec2& other) const
	{
		return x < other.x && y < other.y;
	}

	bool vec2::operator>=(const vec2& other) const
	{
		return x >= other.x || y >= other.y;
	}

	bool vec2::operator<=(const vec2& other) const
	{
		return x <= other.x && y <= other.y;
	}


	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2: " << vector.x << ", " << vector.y;
		return stream;
	}

} }