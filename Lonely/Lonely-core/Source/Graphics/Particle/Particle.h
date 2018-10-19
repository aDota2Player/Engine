#pragma once

#include "Maths.h"

namespace lonely { namespace graphics {
	
	struct ParticleVertexData
	{
		maths::vec2 position;
		maths::vec2 textureCoordinate;
		maths::vec4 color;
	};

	struct Particle
	{
		maths::vec2 position;
		maths::vec2 size;
		maths::vec2 velocity;

		maths::vec4 color;
		maths::vec4 originalColor;

		float life;
		float lifeSpan;

		Particle(): position(0.0f), size(0.0f), velocity(0.0f), color(1.0f), life(0.0f) {}

		Particle(const maths::vec2& position, const maths::vec2& size,
				 const maths::vec2& velocity = maths::vec2(0.0f), const maths::vec4& color = maths::vec4(1.0f))
			: position(position), size(size), velocity(velocity), color(color), life(0.0f) {}
	};

} }


