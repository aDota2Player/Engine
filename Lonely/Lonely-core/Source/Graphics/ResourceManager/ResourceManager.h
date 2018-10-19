#pragma once

#include <map>
#include <string>

#define GL_LINEAR 0x2601
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_NEAREST_MIPMAP_LINEAR 0x2702

namespace lonely { namespace graphics {

	class Texture;
	class Shader;

	class ResourceManager
	{
	public:

		static std::map<std::string, Texture*> Textures;
		static std::map<std::string, Shader*> Shaders;

		
		static Texture* LoadTexture(const std::string& name, const std::string& path, bool flip = false,
								  	unsigned int mag_filter = GL_LINEAR   , unsigned int min_filter = GL_NEAREST_MIPMAP_LINEAR,
									unsigned int wrap_s = GL_CLAMP_TO_EDGE, unsigned int wrap_t = GL_CLAMP_TO_EDGE);
		
		static Texture* GetTexture(const std::string& name);
		

		static Shader* LoadShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path);
		static Shader* LoadShader(const std::string& name,
			      const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& geometry_shader_path);
		static Shader* GetShader(const std::string& name);


		static void DeleteShader(const std::string& name);
		static void DeleteTexture(const std::string& name);


	protected:
		ResourceManager() {}
	};

} }