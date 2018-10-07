#pragma once

#include "Maths/vec2.h"

namespace lonely { namespace maths {

	struct AABB;

	enum Direction;

	struct CircleCollision
	{
		float radius;
		vec2 position;
		vec2 center;

		CircleCollision(float radius, vec2 position);

		bool Contains(const vec2& point);
		bool Intersects(const AABB& other);
		bool Intersects(const CircleCollision& other);

		Direction Collided(const AABB& other);
		Direction Collided(const CircleCollision& other);

		inline void SetPosition(const vec2& position) { this->position = position;  center = position + radius; }
		inline void SetX(float x) { position.x = x; center = position + radius; }
		inline void SetY(float y) { position.y = y; center = position + radius; }
	};

} }