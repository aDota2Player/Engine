#pragma once

#define GL_STATIC_DRAW 0x88E4

namespace lonely { namespace graphics {

	class VertexArray;

	class VertexBuffer
	{
	private:
		friend VertexArray;
		unsigned int m_BufferID;

	public:
		VertexBuffer();

		void Compile(const void* data, unsigned int size, unsigned int usage = GL_STATIC_DRAW);
	};

} }