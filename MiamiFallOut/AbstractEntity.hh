#pragma once
#include "stdafx.h"
#include "ISerialize.hh"
#include "IShapeManager.hh"

class AbstractEntity: ISerialize
{
public:
	AbstractEntity();
	virtual ~AbstractEntity();

	virtual void Draw(sf::RenderWindow*) = 0;
	virtual void Update() = 0;
	virtual void Move() = 0;
	virtual std::string& Serialize() = 0;
	virtual std::string GetEntityType() const = 0;
	virtual sf::Shape* GetShape() const = 0;
	virtual void SetEntityType(std::string type) = 0;
};
