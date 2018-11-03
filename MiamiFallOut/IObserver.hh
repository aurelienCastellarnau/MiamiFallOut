#pragma once

class IObservable;
class IObserver
{
public:
	virtual void Notify(IObservable* observable) = 0;

	virtual ~IObserver() {}
};
