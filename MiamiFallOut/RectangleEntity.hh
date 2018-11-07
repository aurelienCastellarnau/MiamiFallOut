#pragma once
#include "ShapeEntity.hh"
#include "IShapeManager.hh"
#include <SFML/Graphics.hpp>

class RectangleEntity :
	public ShapeEntity
{
public:
	RectangleEntity();

	virtual void Draw(sf::RenderWindow*) override;
	virtual void Update() override;
	virtual std::string& Serialize() override;
	virtual void Move();

	sf::RectangleShape* GetRectangle() const;
	void SetRectangle(float, float, sf::Color);

	~RectangleEntity();
};

