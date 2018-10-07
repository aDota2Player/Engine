#include "Button.h"

namespace lonely { namespace graphics {

	Button::Button(const maths::vec2& position, const maths::vec2& size, Texture* texture, Texture* hoverTex, Texture* pressTex)
		: Sprite(position, size, texture), m_UnPressedTex(texture), m_HoverTex(hoverTex), m_PressTex(pressTex), m_State(UNPRESSED) {}

	bool Button::Clicked(float xpos, float ypos, bool clicked)
	{
		if (xpos > m_Position.x && xpos < m_Position.x + m_Size.x && ypos > m_Position.y && ypos < m_Position.y + m_Size.y && m_State != HOVERED && m_State != PRESSED)
		{
			m_State = HOVERED;
			m_Texture = m_HoverTex;
			return false;
		}

		else if (!(xpos > m_Position.x && xpos < m_Position.x + m_Size.x && ypos > m_Position.y && ypos < m_Position.y + m_Size.y) && m_State == HOVERED)
		{
			m_State = UNPRESSED;
			m_Texture = m_UnPressedTex;
			return false;
		}

		else if (m_State == HOVERED && clicked)
		{
			m_State = PRESSED;
			m_Texture = m_PressTex;
			return false;
		}

		else if (m_State == PRESSED && !clicked)
		{
			if (xpos > m_Position.x && xpos < m_Position.x + m_Size.x && ypos > m_Position.y && ypos < m_Position.y + m_Size.y)
			{
				m_State = RELEASED;
				m_Texture = m_HoverTex;
				return true;
			}
			else
			{
				m_State = HOVERED;
				m_Texture = m_HoverTex;
				return false;
			}
		}

		return false;
	}

} }