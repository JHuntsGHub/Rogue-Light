#include "pch.h"
#include "Time.h"


Time::Time()
{
}


Time::~Time()
{
}

void Time::ResetTimer()
{
	///this is to reset the timer so that delta time is more accurate throughout the program.
}

float Time::GetDeltaTime()
{
	///This should be callable in all gameObject variants. Acts just like Time.deltatime in Unity.
	return 0.0f;
}
