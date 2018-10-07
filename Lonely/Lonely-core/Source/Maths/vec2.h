#pragma once

#include <iostream>

namespace lonely { namespace maths {

	struct vec2
	{
		union 
		{
			struct { float x, y; };
			struct { float r, g; };
			struct { float s, t; };
			struct { float u, v; };
		};

		vec2(                );
		vec2(float x, float y);
		vec2(  float scalar  );

		vec2  Normalize(                 ) const;
		float Magnitude(                 ) const;
		float Distance (const vec2& other) const;
		float Dot      (const vec2& other) const;

		vec2& Add       (const vec2& other);
		vec2& Substract (const vec2& other);
		vec2& Multiply  (const vec2& other);
		vec2& Divide    (const vec2& other);

		vec2& Add       (float value);
		vec2& Substract (float value);
		vec2& Multiply  (float value);
		vec2& Divide    (float value);

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);

		friend vec2 operator-(const vec2& value);

		friend vec2 operator+(vec2 left, float value);
		friend vec2 operator-(vec2 left, float value);
		friend vec2 operator*(vec2 left, float value);
		friend vec2 operator/(vec2 left, float value);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		vec2& operator+=(float value);
		vec2& operator-=(float value);
		vec2& operator*=(float value);
		vec2& operator/=(float value);

		bool operator==(const vec2& other) const;
		bool operator!=(const vec2& other) const;

		bool operator>(const vec2& other)  const;
		bool operator<(const vec2& other)  const;
		bool operator>=(const vec2& other) const;
		bool operator<=(const vec2& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
	};	
	
} }