#include "stdafx.h"
#include <string>
#include "EntityFactory.hh"
#include "CircleEntity.hh"
#include "RectangleEntity.hh"

EntityFactory::EntityFactory()
{
}

ShapeEntity* EntityFactory::Create(const std::string& class_name) {
	
	if (class_name == "CircleEntity") {
		return new CircleEntity();
	}
	else if (class_name == "RectangleEntity") {
		return new RectangleEntity();
	}
	else {
		return NULL;
	}
}

EntityFactory::~EntityFactory()
{
}
