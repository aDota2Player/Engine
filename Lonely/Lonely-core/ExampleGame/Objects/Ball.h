#pragma once

#include "Graphics/Renderer/Sprite.h"
#include "Physics/CircleCollision.h"

using namespace lonely;
using namespace graphics;
using namespace maths;

class Ball : public Sprite
{
public:
	CircleCollision collision;
	maths::vec2 velocity;
	bool stuck;
	
	Ball(float x, float y, float radius, float velocity_x, float velocity_y, Texture* texture);
	
	inline const maths::vec2& GetVelocity() {}

	inline void SetPosition(const maths::vec2& position) override { m_Position = position; collision.SetPosition(position); }
	inline void SetX(float x) override { m_Position.x = x; collision.SetX(x); }
	inline void SetY(float y) override { m_Position.y = y; collision.SetY(y); }
};