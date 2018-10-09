#include "AABB.h"
#include "CircleCollision.h"

#include "Maths.h"

namespace lonely { namespace physics {

	AABB::AABB(const maths::vec2& position, const maths::vec2& size)
		: position(position), size(size)         , max(position + size)                         {}

	AABB::AABB(const maths::vec2& position, float width, float height)
		: position(position), size(width, height), max(position.x + width, position.y + height) {}

	AABB::AABB(float x, float y, float width, float height)
		: position(x, y)    , size(width, height), max(x + width, y + height)                   {}


	bool AABB::Contains(const maths::vec2& point)
	{
		return point >= position && point <= max;
	}

	bool AABB::Intersects(const AABB& other)
	{
		return other.position < max && other.max > position;
	}

	bool AABB::Intersects(const CircleCollision& other)
	{
		maths::vec2 half_extents = size / 2.0f;

		maths::vec2 center(position + half_extents);
		maths::vec2 difference = other.center - center;
		maths::vec2 clamped = clamp(difference, -half_extents, half_extents);

		maths::vec2 closest = center + clamped;
		difference = closest - other.center;

		return maths::length(difference) < other.radius;
	}

} }