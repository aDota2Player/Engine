#pragma once

namespace lonely { namespace graphics {

	class RenderBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		RenderBuffer(unsigned int window_width, unsigned int window_height);
		~RenderBuffer();

		void Bind() const;
		void UnBind() const;

		void SetBufferStorage(unsigned int window_width, unsigned int window_height) const;

		inline unsigned int GetID() const { return m_BufferID; }
	};

} }