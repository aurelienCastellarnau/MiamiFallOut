#include "stdafx.h"
#include <sstream>
#include "ShapeEntity.hh"
#include "IObservable.hh"

/*
ShapeEntity implementation
*/
ShapeEntity::ShapeEntity() : IObservable()
{
	_intersect = false;
}

/*
 AbstractEntity implementation
*/
void ShapeEntity::Draw(sf::RenderWindow* w) {

}

void ShapeEntity::Update() {
}

/*
  IObservable implementation
*/

void ShapeEntity::AddObserver(IObserver * observer)
{
	_observers.push_front(observer);
}

void ShapeEntity::RemoveObserver(IObserver * observer)
{
	_observers.remove(observer);
}

void ShapeEntity::OnNotify()
{
	// std::cout << "\nNotify on ShapeEntity, X="<<GetX()<<" Y="<<GetY();
}

std::string& ShapeEntity::Serialize()
{
	std::string ret = "ShapeEntity";
	return ret;
}

std::string ShapeEntity::GetEntityType() const
{
	return _entity_type;
}

bool ShapeEntity::isPlayer() const
{
	return _entity_type == "player";
}

sf::Shape* ShapeEntity::GetShape() const
{
	return _shape;
}

void ShapeEntity::SetShape(sf::Shape* shape)
{
	_shape = shape;
}

double ShapeEntity::GetX() const
{
	return _x;
}

double ShapeEntity::GetY() const
{
	return _y;
}

bool ShapeEntity::GetIntersect() const
{
	return _intersect;
}

void ShapeEntity::SetEntityType(std::string type)
{
	_entity_type = type;
}

void ShapeEntity::SetX(double x)
{
	if (x < _shape->getLocalBounds().width / 2) {
		_x = _shape->getLocalBounds().width / 2;
	} else if (x + (_shape->getLocalBounds().width / 2) >= 1600 ) {
		_x = 1600 - (_shape->getGlobalBounds().width / 2);
	} else {
		_x = x;
	}

	for (IObserver* it : _observers) 
	{
		it->Notify(this);
	}
}

void ShapeEntity::SetY(double y)
{
	if (y < _shape->getGlobalBounds().height / 2) {
		_y = _shape->getGlobalBounds().height / 2;
	}
	else if (y + (_shape->getGlobalBounds().height / 2) >= 800) {
		_y = 800 - (_shape->getGlobalBounds().height / 2);
	}
	else {
		_y = y;
	}

	for (IObserver* it : _observers)
	{
		it->Notify(this);
	}
}

void ShapeEntity::SetIntersect(bool intersect)
{
	_intersect = intersect;
}

void ShapeEntity::SetCoordonates()
{
	_shape->setPosition(_x, _y);
}

ShapeEntity::~ShapeEntity()
{
}

