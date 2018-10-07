#pragma once

#include <GL/glew.h>

namespace lonely { namespace graphics {

	class RenderBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		RenderBuffer(unsigned int windowWidth, unsigned int windowHeight);
		~RenderBuffer();

		void Bind() const;
		void UnBind() const;

		void SetBufferStorage(unsigned int windowWidth, unsigned int windowHeight) const;

		inline unsigned int GetID() const { return m_BufferID; }
	};

} }