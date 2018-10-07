#include "RenderBuffer.h"

namespace lonely { namespace graphics {

	RenderBuffer::RenderBuffer(unsigned int windowWidth, unsigned int windowHeight)
		: m_BufferID(0)
	{
		glGenRenderbuffers(1, &m_BufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_BufferID);
	}

	void RenderBuffer::Bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID);
	}

	void RenderBuffer::UnBind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void RenderBuffer::SetBufferStorage(unsigned int windowWidth, unsigned int windowHeight) const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

} }