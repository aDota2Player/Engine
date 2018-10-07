#include "Sound.h"

namespace lonely { namespace audio {

	Sound::Sound(const std::string& path)
	{
		m_SoundSource = SoundManager::Engine->addSoundSourceFromFile(path.c_str());
	}

	Sound::~Sound()
	{
		if (m_Sound)
			m_Sound->drop();
		SoundManager::Engine->removeSoundSource(m_SoundSource);
	}

	void Sound::Play(bool loop, bool override)
	{
		if (!m_Sound) // m_Sound == nullptr
		{
			m_Sound = SoundManager::Engine->play2D(m_SoundSource, loop, false, true);
		}
		else if (m_Sound->isFinished() || override)
		{
			m_Sound = SoundManager::Engine->play2D(m_SoundSource, loop, false, true);
		}
		else if (m_Sound->getIsPaused())
		{
			m_Sound->stop();
			m_Sound = SoundManager::Engine->play2D(m_SoundSource, loop, false, true);
		}
	}

	void Sound::Resume()
	{
		m_Sound->setIsPaused(false);
	}

	void Sound::Pause()
	{
		m_Sound->setIsPaused(true);
	}

	void Sound::Stop()
	{
		m_Sound->stop();
	}

} }
