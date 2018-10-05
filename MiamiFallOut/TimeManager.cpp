#include "stdafx.h"
#include <chrono>
#include <iostream>
#include "TimeManager.hh"

// Constructor (private)
TimeManager::TimeManager()
{
}

/*
 Methods
*/
void TimeManager::Start()
{
	_start = std::chrono::system_clock::now();
}

void TimeManager::Update()
{
	_last_call = _update;
	_update = std::chrono::system_clock::now();
}

unsigned int TimeManager::GetElapsedTime() const
{
	std::chrono::duration<double> last_call_duration = _last_call.time_since_epoch();
	std::chrono::milliseconds lcd_milli = std::chrono::duration_cast<std::chrono::milliseconds>(last_call_duration);
	std::chrono::duration<double> update_duration = _update.time_since_epoch();
	std::chrono::milliseconds ud_milli = std::chrono::duration_cast<std::chrono::milliseconds>(update_duration);

	if (lcd_milli.count() == 0 || ud_milli.count() == 0)
	{
		return (0);
	}
	else
	{
		std::chrono::duration<double> elapsed_time = _update.time_since_epoch() -_last_call.time_since_epoch();
		std::chrono::milliseconds et_milli = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time);
		std::chrono::nanoseconds et_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time);
		return et_milli.count();
	}
}

unsigned int TimeManager::GetStartedTime() const
{
	std::chrono::time_point<std::chrono::system_clock> call_time = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = call_time - _start;
	std::chrono::milliseconds diff_milli = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
	std::chrono::nanoseconds diff_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
	return diff_milli.count();
}

// Destructor
TimeManager::~TimeManager()
{
}
