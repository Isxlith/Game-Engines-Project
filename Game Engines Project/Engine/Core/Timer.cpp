#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0) {}

Timer::~Timer() {}

void Timer::Start()
{
	prevTicks = currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks()
{
	// Update prevTicks before so that they won;t be the same
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
	// In seconds
	return (currentTicks - prevTicks) / MILLI_TO_SEC;
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	// Calculate how many milliseconds per frame
	unsigned int milliSecsPerFrame = MILLI_TO_SEC / fps_;
	if (milliSecsPerFrame == 0)
	{
		return 0;
	}

	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currentTicks);
	if (sleepTime > milliSecsPerFrame)
	{
		return milliSecsPerFrame;
	}
	return sleepTime;
}

float Timer::GetCurrentMilli() const
{
	// Return current ticks in milliseconds
	return static_cast<float> (currentTicks);
}

float Timer::GetCurrentTickSec() const
{
	// Return current ticks in seconds
	return currentTicks / MILLI_TO_SEC;
}