#include "stdafx.h"
#include <string>
#include "EntityFactory.hh"
#include "CircleEntity.hh"

EntityFactory::EntityFactory()
{
}

ShapeEntity* EntityFactory::Create(const std::string& class_name) {
	if (class_name == "CircleEntity") {
		return new CircleEntity();
	}
	else {
		return NULL;
	}
}

EntityFactory::~EntityFactory()
{
}
