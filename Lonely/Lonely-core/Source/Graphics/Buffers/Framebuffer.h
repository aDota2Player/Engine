#pragma once

#include "../Texture/Texture.h"

#include "RenderBuffer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"

namespace lonely { namespace graphics {

		class Shader;

		class Framebuffer
		{
		private:
			unsigned int m_BufferID;
			RenderBuffer m_RenderBuffer;
			Texture m_Texture;
			Shader* m_Shader;

			VertexArray m_VertexArray;

		public:
			Framebuffer(unsigned int screen_width, unsigned int screen_height, Shader* shader);
			~Framebuffer();

			void Begin() const;
			void End() const;
			void Draw(bool depth = true) const;

			void SetSize(unsigned int screen_width, unsigned int screen_height) const;
		};

} }
