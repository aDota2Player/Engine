#pragma once

#define GL_STATIC_DRAW 0x88E4

namespace lonely { namespace graphics {

	class VertexBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		VertexBuffer(const void* data, unsigned int size, unsigned int usage = GL_STATIC_DRAW);
		~VertexBuffer();

		void SubData(const void* data, unsigned int size, unsigned int offset = 0);


		void Bind() const;
		void UnBind() const;

	};

} }