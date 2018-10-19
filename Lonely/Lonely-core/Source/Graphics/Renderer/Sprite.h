#pragma once

#include "Maths.h"

#include "../ResourceManager/ResourceManager.h"
#include "../Texture/Texture.h"

#ifndef LONELY_SPRITE_DEFAULTS
#define LONELY_SPRITE_DEFAULTS

#define LONELY_DEFAULT_SPRITE_POSITION_X	0.0f
#define LONELY_DEFAULT_SPRITE_POSITION_Y	0.0f
#define LONELY_DEFAULT_SPRITE_SIZE_X		10.0f
#define LONELY_DEFAULT_SPRITE_SIZE_Y		10.0f

#define LONELY_DEFAULT_SPRITE_COLOR			1.0f
#endif /* LONELY_SPRITE_DEFAULTS */

namespace lonely { namespace graphics {

	struct VertexData
	{
		maths::vec2 position;
		maths::vec2 textureCoordinate;
		float textureID;
		maths::vec4 color;
	};

	class Sprite
	{
	protected:
		maths::vec2 m_Position;
		maths::vec2 m_Size;
		maths::vec4 m_Color;

		Texture* m_Texture;

		bool b_Visible;
	
	public:
		Sprite(
			const maths::vec2& position = maths::vec2(LONELY_DEFAULT_SPRITE_POSITION_X, LONELY_DEFAULT_SPRITE_POSITION_Y), 
			const maths::vec2& size     = maths::vec2(LONELY_DEFAULT_SPRITE_SIZE_X    ,     LONELY_DEFAULT_SPRITE_SIZE_Y),
			Texture* texture = ResourceManager::GetTexture("DEFAULT"), 
			const maths::vec4& color    = maths::vec4(                LONELY_DEFAULT_SPRITE_COLOR                ))
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(texture), b_Visible(true) {}

		virtual ~Sprite() {}

		// Getters
		inline const maths::vec2& GetPosition() const { return m_Position; }
		inline const maths::vec2& GetSize    () const {   return m_Size;   }
		inline const maths::vec4& GetColor   () const {  return m_Color ;  }

		inline float GetX() { return m_Position.x; }
		inline float GetY() { return m_Position.y; }

		inline const unsigned int GetTexID() const { return m_Texture->GetID(); }

		inline const bool IsVisible() const { return b_Visible; }

		// Setters
		virtual inline void SetPosition(const maths::vec2& position) { m_Position = position; }
		virtual inline void SetSize    (const maths::vec2& size    ) {     m_Size = size;     }
		virtual inline void SetColor   (const maths::vec4& color   ) {    m_Color = color;    }

		virtual inline void SetX(float x) { m_Position.x = x; }
		virtual inline void SetY(float y) { m_Position.y = y; }

		virtual inline void SetVisibility(bool visible) { b_Visible = visible; }
	};

} }