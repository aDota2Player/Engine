#pragma once

#include "Graphics/Renderer/Sprite.h"
#include "Physics/AABB.h"

using namespace lonely;
using namespace graphics;
using namespace maths;
using namespace physics;

class GameObject : public lonely::graphics::Sprite
{
private:
	bool m_Solid;

public:
	AABB collision;
	GameObject(float x, float y, float width, float height, bool solid, Texture* texture, maths::vec4 color = maths::vec4(1.0f))
		: Sprite(maths::vec2(x, y), maths::vec2(width, height), texture, color), m_Solid(solid), collision(x, y, width, height) {}

	inline bool Destroyed() { return !b_Visible; }
	inline bool isSolid() { return m_Solid; }

	inline void Destroy() { b_Visible = false; }
};