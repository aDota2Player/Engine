#pragma once

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

#include <map>
#include <string>

namespace lonely { namespace graphics {

	class ResourceManager
	{
	public:

		static std::map<std::string, Texture*> Textures;
		static std::map<std::string, Shader*> Shaders;

		
		static Texture* LoadTexture(const std::string& name, const std::string& path, bool flip = false,
								  	unsigned int mag_filter = GL_LINEAR   , unsigned int min_filter = GL_NEAREST_MIPMAP_LINEAR,
									unsigned int wrap_s = GL_CLAMP_TO_EDGE, unsigned int wrap_t = GL_CLAMP_TO_EDGE);
		
		static Texture* GetTexture(const std::string& name);
		

		static Shader* LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		static Shader* GetShader(const std::string& name);


		static void DeleteShader(const std::string& name);
		static void DeleteTexture(const std::string& name);


	protected:
		ResourceManager() {}
	};

} }