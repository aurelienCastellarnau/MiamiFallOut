#include "stdafx.h"
#include <sstream>
#include "ShapeEntity.hh"
#include "IObservable.hh"

/*
 AbstractEntity implementation
*/
void ShapeEntity::Draw(IShapeManager* shapeManager) {

}

void ShapeEntity::Update() {

}

void ShapeEntity::AddObserver(IObserver * observer)
{
	_observers.push_front(observer);
}

void ShapeEntity::RemoveObserver(IObserver * observer)
{
	_observers.remove(observer);
}

std::string& ShapeEntity::Serialize()
{
	std::string ret = "ShapeEntity";
	return ret;
}

/*
 Character implementation
 */
ShapeEntity::ShapeEntity(): IObservable()
{
}

sf::Shape* ShapeEntity::GetShape() const
{
	return _shape;
}

void ShapeEntity::SetShape(sf::Shape* shape)
{
	_shape = shape;
}

ShapeEntity::~ShapeEntity()
{
}

