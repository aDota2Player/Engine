#pragma once

#include <Windows.h>

#include <GL/glew.h>

namespace lonely {

	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;

	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			if (!QueryPerformanceFrequency(&frequency))
				std::cout << "[ WARNING ]: Your system does not support high resolution timers!" << std::endl;

			m_Frequency = 1.0f / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		void reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Frequency);
		}
	};

	class DeltaTimer
	{
	protected:
		double m_CurrentTime, m_LastTime, m_DeltaTime;

	public:
		DeltaTimer(): m_DeltaTime(0), m_CurrentTime(0), m_LastTime(0) {}

		virtual inline double GetDeltaTime() const { return m_DeltaTime; }

		virtual void Update()
		{
			m_CurrentTime = glfwGetTime();
			m_DeltaTime = m_CurrentTime - m_LastTime;
			m_LastTime = m_CurrentTime;
		}

	};
}