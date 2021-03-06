#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "IShapeManager.hh"
#include "ShapeEntity.hh"
#include "RectangleEntity.hh"


RectangleEntity::RectangleEntity()
	: ShapeEntity()
{
	SetEntityType("RectangleEntity");
}

void RectangleEntity::Draw(sf::RenderWindow* window)
{
	sf::Shape* s = GetShape();
	window->draw(*s);
}

void RectangleEntity::Update()
{
}

std::string & RectangleEntity::Serialize()
{
	std::string ret = "RectangleEntity";
	return ret;
}

void RectangleEntity::Move()
{
	
}

sf::RectangleShape * RectangleEntity::GetRectangle() const
{
	sf::Shape* s = GetShape();
	return dynamic_cast<sf::RectangleShape*>(s);
}

void RectangleEntity::SetRectangle(float sizeX, float sizeY, sf::Color color = sf::Color::Black)
{
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
	shape->setFillColor(color);
	SetShape(shape);
}

RectangleEntity::~RectangleEntity()
{
}
