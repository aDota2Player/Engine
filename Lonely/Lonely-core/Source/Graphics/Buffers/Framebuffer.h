#pragma once

#include <GL/glew.h>

#include "RenderBuffer.h"

#include "../Texture/Texture.h"
#include "../Shader/Shader.h"

#include "VertexArray.h"
#include "VertexBuffer.h"

namespace lonely { namespace graphics {

	class Framebuffer
	{
	private:
		unsigned int m_BufferID;
		RenderBuffer m_RendererBuffer;
		Texture m_Texture;
		Shader m_Shader;
		
		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;

	public:
		Framebuffer(unsigned int screenWidth, unsigned int screenHeight, const std::string& vertexPath, const std::string& fragmentPath);
		~Framebuffer();

		void Begin() const;
		void End() const;
		void Draw() const;

		void SetSize(unsigned int screenWidth, unsigned int screenHeight) const;

	};

} }