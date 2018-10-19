#include "RenderBuffer.h"

#include <GL/glew.h>

namespace lonely { namespace graphics {

	RenderBuffer::RenderBuffer(unsigned int window_width, unsigned int window_height)
		: m_BufferID(0)
	{
		glGenRenderbuffers(1, &m_BufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_width, window_height);
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

	void RenderBuffer::SetBufferStorage(unsigned int window_width, unsigned int window_height) const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_width, window_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

} }