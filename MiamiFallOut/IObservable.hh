#pragma once
#include "IObserver.hh"

class IObservable
{
public:
	virtual void AddObserver(IObserver* observer) = 0;
	virtual void RemoveObserver(IObserver* observer) = 0;
	virtual void OnNotify() = 0;
	virtual ~IObservable() {}
};
