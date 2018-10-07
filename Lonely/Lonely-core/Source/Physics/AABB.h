#pragma once

#include "maths/vec2.h"

namespace lonely { namespace maths {

	struct CircleCollision;

	enum Direction { NONE, LEFT, RIGHT, UP, DOWN };

	struct AABB
	{
		vec2 position, size, max;

		AABB(const vec2& position, const vec2& size);
		AABB(const vec2& position, float width, float height);
		AABB(float x, float y, float width, float height);

		bool Contains(const vec2& point);
		bool Intersects(const AABB& other);
		bool Intersects(const CircleCollision& other);
	
		Direction Collided(const AABB& other);
		Direction Collided(const CircleCollision& other);

		inline void SetPosition(const maths::vec2& position) { this->position = position; max = position + size; }

		inline void SetX(float x) { position.x = x; max = position + size; }
		inline void SetY(float y) { position.y = y; max = position + size; }
	};

} }