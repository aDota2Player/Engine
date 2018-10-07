#pragma once

#include "Maths/vec2.h"
#include "Maths/vec3.h"
#include "Maths/vec4.h"

#include "Maths/mat4.h"

#include <algorithm>
#include <math.h> 


#define LONELY_PI 3.14159265358979323846f

#define LONELY_PI_DIV_180 0.01745329251f
#define LONELY_180_DIV_PI 57.2957795131f

namespace lonely { namespace maths {

	inline float Radians(float degrees)
	{
		return degrees * LONELY_PI_DIV_180;
	}

	inline float Degrees(float radians)
	{
		return radians * LONELY_180_DIV_PI;
	}

	double inline __declspec (naked) __fastcall sqrt(double n)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}

	inline float length(const vec2& value)
	{
		return sqrt(value.x * value.x + value.y * value.y);
	}

	inline float clamp(float value, float min, float max)
	{
		return std::max(min, std::min(value, max));
	}

	inline vec2 clamp(vec2 value, vec2 min, vec2 max)
	{
		return vec2(clamp(value.x, min.x, max.x), clamp(value.y, min.y, max.y));
	}

} }