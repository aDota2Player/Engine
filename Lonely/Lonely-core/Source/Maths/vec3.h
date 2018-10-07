#pragma once

#include <iostream>

namespace lonely { namespace maths {

	struct vec3
	{
		union 
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			struct { float s, t, r; };
		};

		vec3(                         );
		vec3(float x, float y, float z);
		vec3(      float scalar      ) ;

		vec3  Normalize(                 ) const;
		vec3  Cross    (const vec3& other) const;
		float Magnitude(                 ) const;
		float Distance (const vec3& other) const;
		float Dot      (const vec3& other) const;

		vec3& Add       (const vec3& other);
		vec3& Substract (const vec3& other);
		vec3& Multiply  (const vec3& other);
		vec3& Divide    (const vec3& other);

		vec3& Add       (float value);
		vec3& Substract (float value);
		vec3& Multiply  (float value);
		vec3& Divide    (float value);

		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);

		friend vec3 operator+(vec3 left, float value);
		friend vec3 operator-(vec3 left, float value);
		friend vec3 operator*(vec3 left, float value);
		friend vec3 operator/(vec3 left, float value);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		vec3& operator+=(float value);
		vec3& operator-=(float value);
		vec3& operator*=(float value);
		vec3& operator/=(float value);

		bool operator==(const vec3& other) const;
		bool operator!=(const vec3& other) const;

		bool operator>(const vec3& other)  const;
		bool operator<(const vec3& other)  const;
		bool operator>=(const vec3& other) const;
		bool operator<=(const vec3& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
	};	
	
} }