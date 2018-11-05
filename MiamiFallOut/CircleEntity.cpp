#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "IShapeManager.hh"
#include "ShapeEntity.hh"
#include "CircleEntity.hh"
#include "GameManager.hh"


CircleEntity::CircleEntity()
	: ShapeEntity()
{
}

void CircleEntity::Draw(IShapeManager* manager)
{
	sf::Shape* s = GetShape();
	sf::RenderWindow* window = manager->GetWindow();
	window->draw(*s);
}

void CircleEntity::Update()
{
}

std::string & CircleEntity::Serialize()
{
	std::string ret = "CircleEntity";
	return ret;
}

void CircleEntity::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->SetY(this->GetY() + 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		this->SetY(this->GetY() - 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->SetX(this->GetX() - 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->SetX(this->GetX() + 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->GetCircle()->setRotation(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->GetCircle()->rotate(180);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->GetCircle()->rotate(5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->GetCircle()->rotate(-5);
	}
	this->SetCoordonates();
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

CircleEntity::~CircleEntity()
{
}
