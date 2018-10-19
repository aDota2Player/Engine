#include "Texture.h"

#include <stb_image/stb_image.h>

#include <iostream>

namespace lonely { namespace graphics {

	Texture::Texture(const std::string& filePath, bool flip,
	   	             unsigned int mag_filter, unsigned int min_filter, unsigned int wrap_s, unsigned int wrap_t)
		: m_TextureID(0)
	{
		int width, height, components;

		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &components, LONELY_TEXTURE_REQUIRED_COMPONENTS);
		glGenTextures(1, &m_TextureID);

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
			b_SuccessfullLoad = true;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

			unsigned int format;
			if (components == 1)
				format = GL_RED;
			if (components == 3)
				format = GL_RGB;
			if (components == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}
		else 
		{
			std::cout << "[ WARNING ]: Failed to load texture at location: " << filePath << std::endl;
			b_SuccessfullLoad = false;
			stbi_image_free(data);
		}
	}

	Texture::Texture(unsigned int screen_width, unsigned int screen_height)
		: m_TextureID(0), b_SuccessfullLoad(1)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(unsigned int width, unsigned int rows, unsigned char* buffer)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, rows, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetSize(unsigned int screen_width, unsigned int screen_height) const
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} }