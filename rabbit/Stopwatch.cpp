#include "pch.h"
#include "Stopwatch.h"
#include <Windows.h>

u64 GetFrequency()
{
	LARGE_INTEGER frequency;

	if (!QueryPerformanceFrequency(&frequency))
	{
		std::wcout << "Failed to query performance frequency, all timers will always return 0" << std::endl;
		return 0;
	}

	return frequency.QuadPart;
}

u64 GetCurrentPerformanceTimer()
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
	return static_cast<f32>(static_cast<f64>(GetCurrentPerformanceTimer() - gFrequency) / gFrequency);
}

void Stopwatch::Restart()
{
	myStartTime = GetCurrentPerformanceTimer();
}
