#include "stdafx.h"
#include <sstream>
#include "ShapeEntity.hh"
#include "IObservable.hh"

/*
ShapeEntity implementation
*/
ShapeEntity::ShapeEntity() : IObservable()
{
}

/*
 AbstractEntity implementation
*/
void ShapeEntity::Draw(IShapeManager* shapeManager) {

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
	std::cout << "\nNotify on ShapeEntity, X="<<GetX()<<" Y="<<GetY();
}

std::string& ShapeEntity::Serialize()
{
	std::string ret = "ShapeEntity";
	return ret;
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

void ShapeEntity::SetX(double x)
{

	if (x < 0) {
		_x = 0;
	} else if (x + _shape->getGlobalBounds().width >= 1600 ) {
		_x = 1600 - _shape->getGlobalBounds().width;
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
	if (y < 0) {
		_y = 0;
	}
	else if (y + _shape->getGlobalBounds().height >= 800) {
		_y = 800 - _shape->getGlobalBounds().height;
	}
	else {
		_y = y;
	}

	for (IObserver* it : _observers)
	{
		it->Notify(this);
	}
}

void ShapeEntity::SetCoordonates()
{
	_shape->setPosition(_x, _y);
}

ShapeEntity::~ShapeEntity()
{
}

