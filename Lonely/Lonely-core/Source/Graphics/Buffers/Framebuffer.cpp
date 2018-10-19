#include "Framebuffer.h"

#include "../Shader/Shader.h"


#include <GL/glew.h>

namespace lonely { namespace graphics {

		Framebuffer::Framebuffer(unsigned int screen_width, unsigned int screen_height, Shader* shader)
			: m_Texture(screen_width, screen_height), m_RenderBuffer(screen_width, screen_height), m_Shader(shader)
		{
			glGenFramebuffers(1, &m_BufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture.GetID(), 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer.GetID());

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				__debugbreak(); // Framebuffer did not completed successfully

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			float vertices[] = {
			   -1.0f,  1.0f,  0.0f, 1.0f,
			   -1.0f, -1.0f,  0.0f, 0.0f,
				1.0f, -1.0f,  1.0f, 0.0f,

			   -1.0f,  1.0f,  0.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
				1.0f,  1.0f,  1.0f, 1.0f
			};

			VertexBuffer vertexBuffer;
			vertexBuffer.Compile(vertices, sizeof(vertices), GL_STATIC_DRAW);

			m_VertexArray.BindArray();
			m_VertexArray.Push<float>(2, GL_FLOAT, GL_FALSE);
			m_VertexArray.Push<float>(2, GL_FLOAT, GL_FALSE);
			m_VertexArray.Compile(vertexBuffer);

			m_VertexArray.UnBindArray();
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, &m_BufferID);
		}

		void Framebuffer::Begin() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Framebuffer::End() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Framebuffer::Draw(bool depth) const
		{
			m_Shader->Bind();
			m_Texture.Bind();
			m_VertexArray.BindArray();

			glDisable(GL_DEPTH_TEST);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			if (depth)
				glEnable(GL_DEPTH_TEST);
		}

		void Framebuffer::SetSize(unsigned int screen_width, unsigned int screen_height) const
		{
			m_RenderBuffer.SetBufferStorage(screen_width, screen_height);
			m_Texture.SetSize(screen_width, screen_height);
		}

} }
