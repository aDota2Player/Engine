#include "SoundManager.h"

#include "Sound.h"

#include <iostream>

namespace lonely { namespace audio {
	
	irrklang::ISoundEngine* SoundManager::Engine;
	std::map<std::string, Sound*> SoundManager::Sounds;

	Sound* SoundManager::LoadSound(const std::string& name, const std::string& path)
	{
		return Sounds[name] = new Sound(path);
	}

	Sound* SoundManager::GetSound(const std::string& name)
	{
		return Sounds[name];
	}

	void SoundManager::Initialize()
	{
		Engine = irrklang::createIrrKlangDevice();
	}

	void SoundManager::Destroy()
	{
		std::map<std::string, Sound*>::iterator it;
		for (it = Sounds.begin(); it != Sounds.end(); ++it)
			delete it->second;
	
		Engine->removeAllSoundSources();
		Engine->drop();
	}

} }