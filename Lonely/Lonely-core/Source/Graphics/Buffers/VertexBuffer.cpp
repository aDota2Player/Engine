#include "VertexBuffer.h"

#include <GL/glew.h>

namespace lonely { namespace graphics {

	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_BufferID);
	}

	void VertexBuffer::Compile(const void* data, unsigned int size, unsigned int usage)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
		
} }