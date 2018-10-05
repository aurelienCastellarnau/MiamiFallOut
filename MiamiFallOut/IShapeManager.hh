#pragma once
#include <SFML/Graphics.hpp>

class IShapeManager;
class IShapeManager
{
public:
	virtual sf::RenderWindow* GetWindow() const = 0;
	virtual void SetWindow(sf::RenderWindow* w) = 0;

	virtual ~IShapeManager() {}
};
