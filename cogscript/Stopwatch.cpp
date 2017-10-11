#include "pch.h"
#include "Stopwatch.h"
#include <Windows.h>

static LONGLONG GetFrequency()
{
	LARGE_INTEGER frequency;

	if (!QueryPerformanceFrequency(&frequency))
	{
		std::wcout << "Failed to query performance frequency, all timers will always return 0" << std::endl;
		return 0;
	}

	return frequency.QuadPart;
}

static LONGLONG GetCurrentPerformanceTimer()
{
	LARGE_INTEGER timer;
	if (!QueryPerformanceCounter(&timer))
		return 0;
	return timer.QuadPart;
}

static f64 gFrequency = static_cast<f64>(GetFrequency());

Stopwatch::Stopwatch()
{
	Restart();
}

Stopwatch::~Stopwatch()
{
}

f32 Stopwatch::GetElapsedTimeInSeconds() const
{
	return static_cast<f32>(static_cast<f64>(GetCurrentPerformanceTimer() - myStartTime) / gFrequency);
}

void Stopwatch::Restart()
{
	myStartTime = GetCurrentPerformanceTimer();
}
