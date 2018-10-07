#include "Ball.h"


Ball::Ball(float x, float y, float radius, float velocity_x, float velocity_y, Texture* texture): 
	Sprite(maths::vec2(x, y), maths::vec2(radius * 2, radius * 2), texture, maths::vec4(1.0f)),
	collision(radius, maths::vec2(x, y)), velocity(velocity_x, velocity_y), stuck(true) {}