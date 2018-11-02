#pragma once
#include "ShapeEntity.hh"
#include "IShapeManager.hh"
#include <SFML/Graphics.hpp>

class RectangleEntity :
	public ShapeEntity
{
public:
	RectangleEntity();

	virtual void Draw(IShapeManager*) override;
	virtual void Update() override;
	virtual std::string& Serialize() override;
	virtual void Move() override;

	sf::RectangleShape* GetRectangle() const;
	void SetRectangle(float, float, sf::Color);

	~RectangleEntity();
};

