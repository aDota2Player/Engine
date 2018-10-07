#pragma once

#include "Maths.h"

#include "Sprite.h"
#include "Renderer.h"

#include "Graphics/Shader/Shader.h"

#include <vector>

namespace lonely { namespace graphics {

	class Layer
	{
	protected:
		std::vector<Sprite*> m_Sprites;

		maths::mat4 m_ProjectionMatrix;

		Renderer* m_Renderer;
		Shader* m_Shader;

	public:
		Layer(Shader* shader, const maths::mat4& projectionMatrix);
		virtual ~Layer();

		virtual void Bind() const;
		virtual void UnBind() const;

		/*
		! WARNING: Once you added a sprite, do not delete the sprite with "delete" keyword.
		!		   If you do so, it will cause error for submitting invalid sprite in renderer.
		!          Use "Remove" function from Layer class to remove a sprite from memory.

		*/
		virtual void Add(Sprite* sprite);
		virtual void Remove(Sprite* sprite);
		virtual void Render();

		virtual void SetProjectionMatrix(const maths::mat4& projectionMatrix);
		virtual void SetModelMatrix(const maths::mat4& modelMatrix);
		virtual void SetViewMatrix(const maths::mat4& viewMatrix);

		virtual void SetModelViewMatrix(const maths::mat4& modelMatrix, const maths::mat4& viewMatrix);

		inline std::vector<Sprite*> GetSprites() { return m_Sprites; }
	};

} }