#pragma once

#include "Maths/vec2.h"

namespace lonely { namespace physics {

	struct AABB;

	enum Direction { NONE, LEFT, RIGHT, UP, DOWN };

	struct CircleCollision
	{
		float radius;
		maths::vec2 position;
		maths::vec2 center;

		CircleCollision(float radius, maths::vec2 position);

		bool Contains(const maths::vec2& point);
		bool Intersects(const AABB& other);
		bool Intersects(const CircleCollision& other);

		Direction Collided(const AABB& other);

		inline void SetPosition(const maths::vec2& position) { this->position = position;  center = position + radius; }
		inline void SetX(float x) { position.x = x; center = position + radius; }
		inline void SetY(float y) { position.y = y; center = position + radius; }
	};

} }