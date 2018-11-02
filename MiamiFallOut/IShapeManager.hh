#pragma once
#include "stdafx.h"
#include "IObserver.hh"

class IShapeManager;
class IShapeManager
{
public:
	virtual sf::RenderWindow* GetWindow() const = 0;
	virtual void SetWindow(sf::RenderWindow* w) = 0;

	virtual ~IShapeManager() {}
};
