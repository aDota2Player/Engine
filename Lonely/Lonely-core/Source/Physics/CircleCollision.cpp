#include "CircleCollision.h"
#include "AABB.h"

#include "Maths.h"

namespace lonely { namespace maths {

		CircleCollision::CircleCollision(float radius, vec2 position) : radius(radius), position() {}

		bool CircleCollision::Contains(const vec2& point)
		{
			return length(center - point) < radius;
		}

		bool CircleCollision::Intersects(const AABB& other)
		{
			vec2 other_half_extents = other.size / 2.0f;

			vec2 other_center(other.position + other_half_extents);
			vec2 difference = center - other_center;
			vec2 clamped = clamp(difference, -other_half_extents, other_half_extents);
			
			vec2 closest = other_center + clamped;
			difference = closest - center;

			return length(difference) < radius;
		}

		bool CircleCollision::Intersects(const CircleCollision& other)
		{
			return length(center - other.center) < radius * 2;
		}

		Direction CircleCollision::Collided(const AABB& other)
		{
			vec2 other_half_extents = other.size / 2.0f;

			vec2 other_center(other.position + other_half_extents);
			vec2 difference = center - other_center;
			vec2 clamped = clamp(difference, -other_half_extents, other_half_extents);

			vec2 closest = other_center + clamped;
			difference = closest - center;

			
			if (length(difference) < radius)
			{
				maths::vec2 compass[] = {
					maths::vec2(1.0f, 0.0f),	// left
					maths::vec2(-1.0f, 0.0f),	// right
					maths::vec2(0.0f, 1.0f),	// up
					maths::vec2(0.0f, -1.0f),	// down
				};
				float max = 0.0f;
				unsigned int best_match = -1;
				for (unsigned int i = 1; i < 5; i++)
				{
					vec2 norm = difference.Normalize();
					float dot_product = norm.Dot(compass[i - 1]);

					if (dot_product > max)
					{
						max = dot_product;
						best_match = i;
					}
				}
				return (Direction)best_match;
			}
			return NONE;
		}

		Direction Collided(const CircleCollision& other)
		{
			return NONE;
		}

} }




