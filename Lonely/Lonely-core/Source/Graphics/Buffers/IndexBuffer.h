#pragma once

namespace lonely { namespace graphics {

	class IndexBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		IndexBuffer(unsigned int* data, unsigned int count);
		IndexBuffer(unsigned short* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void UnBind() const;
	};

} }