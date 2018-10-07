#include "ResourceManager.h"


namespace lonely { namespace graphics {

	std::map<std::string, Texture*> ResourceManager::Textures;
	std::map<std::string, Shader*>  ResourceManager::Shaders;

	Texture* ResourceManager::LoadTexture(const std::string& name, const std::string& path, bool flip,
		unsigned int mag_filter, unsigned int min_filter,
		unsigned int wrap_s, unsigned int wrap_t)
	{
#ifdef _DEBUG
		if (Textures.find(name) != Textures.end())
			return Textures[name];

		Texture* texture = new Texture(path, flip, mag_filter, min_filter, wrap_s, wrap_t);

		if (texture->IsLoaded())
			return Textures[name] = texture;
		else
			return Textures["DEFAULT"];
#else
		return Textures[name] = new Texture(path, flip, mag_filter, min_filter, wrap_s, wrap_t);
#endif
	}

	Texture* ResourceManager::GetTexture(const std::string& name)
	{
		if (Textures.find(name) != Textures.end())
			return Textures[name];
		else
			return Textures["DEFAULT"];
	}

	Shader* ResourceManager::LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
	{
		return Shaders[name] = new Shader(name, vertexPath, fragmentPath);
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