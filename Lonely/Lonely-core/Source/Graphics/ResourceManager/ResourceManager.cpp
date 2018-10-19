#include "ResourceManager.h"

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

namespace lonely { namespace graphics {

	std::map<std::string, Texture*> ResourceManager::Textures;
	std::map<std::string, Shader*>  ResourceManager::Shaders;

	Texture* ResourceManager::LoadTexture(const std::string& name, const std::string& path, bool flip,
		unsigned int mag_filter, unsigned int min_filter,
		unsigned int wrap_s, unsigned int wrap_t)
	{
		if (Textures.find(name) != Textures.end())
			return Textures[name];

		Texture* texture = new Texture(path, flip, mag_filter, min_filter, wrap_s, wrap_t);

		if (texture->IsLoaded())
			return Textures[name] = texture;
		else
			return Textures["DEFAULT"];
	}

	Texture* ResourceManager::GetTexture(const std::string& name)
	{
		if (Textures.find(name) != Textures.end())
			return Textures[name];
		else
			return Textures["DEFAULT"];
	}

	Shader* ResourceManager::LoadShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path)
	{
		return Shaders[name] = new Shader(name, vertex_shader_path, fragment_shader_path);
	}

	Shader* ResourceManager::LoadShader(const std::string& name,
		const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& geometry_shader_path)
	{
		return Shaders[name] = new Shader(name, vertex_shader_path, fragment_shader_path, geometry_shader_path);
	}
	
	Shader* ResourceManager::GetShader(const std::string& name)
	{
		if (Shaders.find(name) != Shaders.end())
			return Shaders[name];
		else
			return Shaders["DEFAULT"];
	}

	void ResourceManager::DeleteShader(const std::string& name)
	{
		delete Shaders[name];
		Shaders.erase(name);
	}

	void ResourceManager::DeleteTexture(const std::string& name)
	{
		delete Textures[name];
		Textures.erase(name);
	}

} }