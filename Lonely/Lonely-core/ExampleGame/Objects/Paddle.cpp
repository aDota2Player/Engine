#include "Paddle.h"


Paddle::Paddle(float x, float y, float width, float height, double speed, Texture* texture)
	: Sprite(maths::vec2(x, y), maths::vec2(width, height), texture),
	  collision(maths::vec2(x, y), maths::vec2(width, height)), speed(speed) {}
