#pragma once

#include "Graphics/Renderer/Sprite.h"
#include "Physics/AABB.h"

using namespace lonely;
using namespace graphics;
using namespace maths;
using namespace physics;

class Paddle : public Sprite
{
public:
	AABB collision;
	double speed;

	Paddle(float x, float y, float width, float height, double speed, Texture* texture);

	inline double GetSpeed() { return speed; }

	inline void SetSpeed(double speed) { speed = speed; }

	inline void SetPosition(const maths::vec2& position) override 
	{ m_Position = position; collision.position = position; collision.max = m_Size + position; }

	inline void SetX(float x) override { m_Position.x = x; collision.SetX(x); }
	inline void SetY(float y) override { m_Position.y = y; collision.SetY(y); }

};