#pragma once

#include "Renderer.h"
#include "Maths/mat4.h"

#include <vector>

namespace lonely { namespace graphics {

	class Shader;
	class Sprite;

	class Layer
	{
	protected:
		std::vector<Sprite*> m_Sprites;

		maths::mat4 m_ProjectionMatrix;

		Renderer m_Renderer;
		Shader* m_Shader;

	public:
		Layer(Shader* shader, const maths::mat4& projection_matrix);
		virtual ~Layer();

		/*
		! WARNING: Once you added a sprite, do not delete the sprite with "delete" keyword.
		!		   If you do so, it will cause error for submitting invalid sprite in renderer.
		!          Use "Remove" function from Layer class to remove a sprite from memory.

		*/
		virtual void Add(Sprite* sprite);
		virtual void Remove(Sprite* sprite);

		virtual void Render();
		virtual void Render(const maths::mat4& projection_matrix);
		virtual void Render(const maths::mat4& projection_matrix, const maths::mat4& view_matrix);

		inline std::vector<Sprite*> GetSprites() { return m_Sprites; }
	};

} }