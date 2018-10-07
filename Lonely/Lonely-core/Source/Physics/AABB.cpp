#include "AABB.h"
#include "CircleCollision.h"

#include "Maths.h"

namespace lonely { namespace maths {

	AABB::AABB(const vec2& position, const vec2& size)
		: position(position), size(size)         , max(position + size)                         {}

	AABB::AABB(const vec2& position, float width, float height)
		: position(position), size(width, height), max(position.x + width, position.y + height) {}

	AABB::AABB(float x, float y, float width, float height)
		: position(x, y)    , size(width, height), max(x + width, y + height)                   {}


	bool AABB::Contains(const vec2& point)
	{
		return point >= position && point <= max;
	}

	bool AABB::Intersects(const AABB& other)
	{
		return other.position < max && other.max > position;
	}

	bool AABB::Intersects(const CircleCollision& other)
	{
		vec2 half_extents = size / 2.0f;

		vec2 center(position + half_extents);
		vec2 difference = other.center - center;
		vec2 clamped = clamp(difference, -half_extents, half_extents);

		vec2 closest = center + clamped;
		difference = closest - other.center;

		return length(difference) < other.radius;
	}

	Direction AABB::Collided(const AABB& other)
	{
		if (other.position < max && other.max > position)
		{

		}
		
		return NONE;
	}

	Direction AABB::Collided(const CircleCollision& other)
	{
		vec2 half_extents = size / 2.0f;

		vec2 center(position + half_extents);
		vec2 difference = other.center - center;
		vec2 clamped = clamp(difference, -half_extents, half_extents);

		vec2 closest = center + clamped;

		if (length(difference) < other.radius)
		{

		}
		return NONE;
	}


} }