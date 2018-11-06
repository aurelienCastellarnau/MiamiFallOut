#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "IShapeManager.hh"
#include "ShapeEntity.hh"
#include "CircleEntity.hh"
#include "GameManager.hh"


CircleEntity::CircleEntity()
	: ShapeEntity()
{
	SetEntityType("CircleEntity");
}

void CircleEntity::Draw(sf::RenderWindow* window)
{
	sf::Shape* s = GetShape();
	window->draw(*s);
	std::cout << "Circle Entity";
}

void CircleEntity::Update()
{
}

std::string & CircleEntity::Serialize()
{
	std::string ret = "CircleEntity";
	return ret;
}


sf::CircleShape * CircleEntity::GetCircle() const
{
	sf::Shape* s = GetShape();
	return dynamic_cast<sf::CircleShape*>(s);
}

void CircleEntity::SetCircle(float radius, std::size_t pointCount = 30, sf::Color color = sf::Color::Black)
{
	sf::CircleShape* shape = new sf::CircleShape(radius, pointCount);
	shape->setFillColor(color);
	SetShape(shape);
}

void CircleEntity::Move(){}

CircleEntity::~CircleEntity()
{
}
