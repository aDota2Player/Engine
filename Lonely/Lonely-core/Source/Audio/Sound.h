#pragma once

#include <string>

namespace irrklang { class ISoundSource; class ISound; }

namespace lonely { namespace audio {

	class Sound
	{
	protected:
		irrklang::ISoundSource* m_SoundSource;
		irrklang::ISound* m_Sound;
	
	public:
		Sound(const std::string& path);
		~Sound();

		void Play(bool loop = false, bool override = false);
		void Resume();
		
		void Pause();
		void Stop();
	};

} }