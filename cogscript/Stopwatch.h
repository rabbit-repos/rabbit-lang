#pragma once

class Stopwatch
{
public:
	Stopwatch();
	~Stopwatch();

	f32 GetElapsedTimeInSeconds() const;
	void Restart();

private:
	u64 myStartTime;
};
