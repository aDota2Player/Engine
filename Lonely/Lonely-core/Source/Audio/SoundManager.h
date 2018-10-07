#pragma once

#include <irrKlang.h>

#include <map>
#include <string>

namespace lonely { namespace audio {
	
	class Sound;

	class SoundManager
	{
	private:
		friend class Sound;

		static irrklang::ISoundEngine* Engine;
		static std::map<std::string, Sound*> Sounds;

	public:
		static Sound* LoadSound(const std::string& name, const std::string& path);
		static Sound* GetSound(const std::string& name);
		
		static void Initialize();

		static void Destroy();

	private:
		SoundManager() { }
	};

} }