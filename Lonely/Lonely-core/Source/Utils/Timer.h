#pragma once

#include <Windows.h>

#include <GL/glew.h>

#include <iostream>

namespace lonely {

	class Timer
	{
	protected:
		LARGE_INTEGER m_Start;
		double m_DeltaTime, m_CurrentTime, m_LastTime;
		double m_Frequency;

	public:
		Timer()
			: m_DeltaTime(0), m_CurrentTime(0), m_LastTime(0)
		{
			LARGE_INTEGER frequency;
			if (!QueryPerformanceFrequency(&frequency))
				std::cout << "[ WARNING ]: Your system does not support high resolution timers!" << std::endl;

			m_Frequency = 1.0f / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		virtual void reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		virtual void Update()
		{
			m_CurrentTime = ElapsedTime();
			m_DeltaTime = m_CurrentTime - m_LastTime;
			m_LastTime = m_CurrentTime;
		}

		virtual inline float ElapsedTime()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Frequency);
		}

		virtual inline double DeltaTime() const { return m_DeltaTime; }
	};

}