#pragma once

#include "maths/vec2.h"

namespace lonely { namespace physics {

	struct CircleCollision;

	struct AABB
	{
		maths::vec2 position, size, max;

		AABB(const maths::vec2& position, const maths::vec2& size);
		AABB(const maths::vec2& position, float width, float height);
		AABB(float x, float y, float width, float height);

		bool Contains(const maths::vec2& point);
		bool Intersects(const AABB& other);
		bool Intersects(const CircleCollision& other);
	
		inline void SetPosition(const maths::vec2& position) { this->position = position; max = position + size; }

		inline void SetX(float x) { position.x = x; max = position + size; }
		inline void SetY(float y) { position.y = y; max = position + size; }
	};

} }