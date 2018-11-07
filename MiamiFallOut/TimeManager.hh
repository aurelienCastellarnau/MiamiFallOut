#pragma once
#include <chrono>
#include <iostream>

using namespace std::chrono;

class TimeManager
{
	
public:
	// pas singleton

	// Singleton accessor
	// Singleton accessor (public)
	TimeManager();

	/*
	Methods
	*/
	void Start();
	void Update();
	unsigned int GetElapsedTime() const;
	unsigned int GetStartedTime() const;
	unsigned int GetRandomInt(int a, int b);

	// Destructor
	~TimeManager();
	// Operateur de copie et d'affectation delete
	TimeManager(const TimeManager &) = delete;
	TimeManager &operator=(const TimeManager &) = delete;

private:
	

	/*
	Properties
	*/
	milliseconds _ms;
	time_point<system_clock> _start;
	time_point<system_clock> _update;
	time_point<system_clock> _last_call;
};
