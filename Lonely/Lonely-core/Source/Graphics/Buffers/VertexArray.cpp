#include "VertexArray.h"
#include "VertexBuffer.h"

#include <iostream>

#include <GL/glew.h>

namespace lonely { namespace graphics {

	VertexArray::VertexArray()
		: m_ArrayID(0), m_Stride(0)
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexArray::BufferSubData(const void* data, unsigned int size, unsigned int offset)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void VertexArray::BindBuffer() const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexArray::UnBindBuffer() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexArray::BindArray() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::UnBindArray() const 
	{
		glBindVertexArray(0);
	}

	void VertexArray::Compile(const VertexBuffer& buffer)
	{
		m_BufferID = buffer.m_BufferID;
		unsigned int offset = 0;

		BindBuffer();
		BindArray();
		
		for (unsigned int i = 0; i < m_Elements.size(); i++)
		{
			const auto& element = m_Elements[i];

			glVertexAttribPointer(i, element.count, element.type, element.normalized, m_Stride, (const void*)offset);
			glEnableVertexAttribArray(i);
			offset += element.count * SizeOfType(element.type);
		}
		
		UnBindArray();
		UnBindBuffer();
		m_Elements.clear();
	}
	
	unsigned int VertexArray::SizeOfType(unsigned int type) // static private
	{
		switch (type)
		{
		case GL_BYTE:			return 1;
		case GL_UNSIGNED_BYTE:	return 1;
		case GL_SHORT:			return 2;
		case GL_UNSIGNED_SHORT: return 2;
		case GL_INT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_FLOAT:			return 4;
		case GL_DOUBLE:			return 8;
		}
		std::cout << "[ ERROR ]: Failed to find size of type: " << type << std::endl;
		__debugbreak();
		return 0;
	}

} }

