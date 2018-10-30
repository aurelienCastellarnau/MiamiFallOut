#pragma once
#include <string>
#include "ShapeEntity.hh"

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	ShapeEntity* Create(const std::string& class_name);
};
