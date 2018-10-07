#include "vec3.h"

namespace lonely { namespace maths {

	vec3::vec3()						  : x(0), y(0), z(0)			    {}
	vec3::vec3(float x, float y, float z) : x(x), y(y), z(z)			    {}
	vec3::vec3(float scalar)			  : x(scalar), y(scalar), z(scalar) {}


	vec3 vec3::Normalize() const
	{
		float length = Magnitude();
		return vec3(x / length, y / length, z / length);
	}

	float vec3::Magnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	vec3 vec3::Cross(const vec3& other) const
	{
		return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	float vec3::Distance(const vec3& other) const
	{
		float X = x - other.x;
		float Y = y - other.y;
		float Z = z - other.z;
		return sqrt(X * X + Y * Y + Z * Z);
	}

	float vec3::Dot(const vec3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}


	vec3& vec3::Add(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::Substract(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::Multiply(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::Divide(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}


	vec3& vec3::Add(float value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}

	vec3& vec3::Substract(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	vec3& vec3::Multiply(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	vec3& vec3::Divide(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}


	vec3 operator+(vec3 left, const vec3& right)
	{
		return left.Add(right);
	}

	vec3 operator-(vec3 left, const vec3& right)
	{
		return left.Substract(right);
	}
	
	vec3 operator*(vec3 left, const vec3& right)
	{
		return left.Multiply(right);
	}
	
	vec3 operator/(vec3 left, const vec3& right)
	{
		return left.Divide(right);
	}


	vec3 operator+(vec3 left, float value)
	{
		return vec3(left.x + value, left.y + value, left.z + value);
	}

	vec3 operator-(vec3 left, float value)
	{
		return vec3(left.x - value, left.y - value, left.z - value);
	}

	vec3 operator*(vec3 left, float value)
	{
		return vec3(left.x * value, left.y * value, left.z * value);
	}

	vec3 operator/(vec3 left, float value)
	{
		return vec3(left.x / value, left.y / value, left.z / value);
	}


	vec3& vec3::operator+=(const vec3& other)
	{
		return Add(other);
	}

	vec3& vec3::operator-=(const vec3& other)
	{
		return Substract(other);
	}

	vec3& vec3::operator*=(const vec3& other)
	{
		return Multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other)
	{
		return Divide(other);
	}


	vec3& vec3::operator+=(float value)
	{
		return Add(value);
	}

	vec3& vec3::operator-=(float value)
	{
		return Substract(value);
	}

	vec3& vec3::operator*=(float value)
	{
		return Multiply(value);
	}

	vec3& vec3::operator/=(float value)
	{
		return Divide(value);
	}


	bool vec3::operator==(const vec3& other) const
	{

		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(const vec3& other) const
	{
		return !(*this == other);
	}


	bool vec3::operator>(const vec3& other) const
	{
		return x > other.x && y > other.y && z > other.z;
	}

	bool vec3::operator<(const vec3& other) const
	{
		return x < other.x && y < other.y && z < other.z;
	}

	bool vec3::operator>=(const vec3& other) const
	{
		return x >= other.x && y >= other.y && z >= other.z;
	}

	bool vec3::operator<=(const vec3& other) const
	{
		return x <= other.x && y <= other.y && z <= other.z;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector)
	{
		stream << "vec3: " << vector.x << ", " << vector.y << ", " << vector.z;
		return stream;
	}

} }
