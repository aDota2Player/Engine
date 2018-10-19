#pragma once

#include "Graphics/Renderer/Sprite.h"

namespace lonely { namespace graphics {

	enum ButtonState { UNPRESSED = 0, HOVERED, PRESSED, RELEASED };

	class Button : public Sprite
	{
	private:
		Texture* m_UnPressedTex;
		Texture* m_HoverTex; 
		Texture* m_PressTex;

		ButtonState m_State;

	public:
		Button(const maths::vec2& position, const maths::vec2& size,
			   Texture* texture, Texture* hover_texture, Texture* press_texture);
		bool Clicked(float xpos, float ypos, bool clicked);
	};

} }