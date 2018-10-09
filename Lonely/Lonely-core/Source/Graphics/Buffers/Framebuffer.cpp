#include "Framebuffer.h"

namespace lonely {
	namespace graphics {

		Framebuffer::Framebuffer(unsigned int screenWidth, unsigned int screenHeight,
			                     const std::string& vertexPath, const std::string& fragmentPath)
			: m_Texture(screenWidth, screenHeight), m_RendererBuffer(screenWidth, screenHeight),
			  m_Shader("LONELY_FRAGMENT_BUFFER_SHADER", vertexPath, fragmentPath)
	{
		glGenFramebuffers(1, &m_BufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture.GetID(), 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererBuffer.GetID());

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

		glGenVertexArrays(1, &m_VertexArray);
		glGenBuffers(1, &m_VertexBuffer);

		glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);


		glBufferData(GL_ARRAY_BUFFER, 4 * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		glBindVertexArray(m_VertexArray);
		
		glDisable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		if(depth)
			glEnable(GL_DEPTH_TEST);
	}

	void Framebuffer::SetSize(unsigned int screenWidth, unsigned int screenHeight) const
	{
		m_RendererBuffer.SetBufferStorage(screenWidth, screenHeight);
		m_Texture.SetSize(screenWidth, screenHeight);
	}

	

} }
