	#pragma once

#include <string>

#include <GL/glew.h>

#define TEXTURE_REQUIRED_COMPONENTS 4

namespace lonely { namespace graphics {

	class Texture
	{
	private:
		unsigned int m_TextureID;

		bool b_SuccessfullLoad;

	public:
		// Image Texture
		Texture(const std::string& filePath, bool flip = false,
			    unsigned int mag_filter = GL_LINEAR       , unsigned int min_filter = GL_NEAREST_MIPMAP_LINEAR,
			    unsigned int wrap_s     = GL_CLAMP_TO_EDGE, unsigned int wrap_t     = GL_CLAMP_TO_EDGE);

		// Framebuffer Texture
		Texture(unsigned int screenWidth, unsigned int screenHeight);

		// Font Texture
		Texture(unsigned int width, unsigned int rows, unsigned char* buffer);
		
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void UnBind() const;

		void SetSize(unsigned int screenWidth, unsigned int screenHeight) const;

		inline const unsigned int GetID() const { return m_TextureID; }
		inline bool IsLoaded() const { return b_SuccessfullLoad; }
	};

} }