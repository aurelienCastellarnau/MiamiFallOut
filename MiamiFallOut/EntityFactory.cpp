#include "stdafx.h"
#include <string>
#include "EntityFactory.hh"
#include "CircleEntity.hh"
#include "RectangleEntity.hh"
#include "Player.hh"
#include "Enemy.hh"

EntityFactory::EntityFactory()
{
}

ShapeEntity* EntityFactory::Create(const std::string& class_name) {
	
	if (class_name == "CircleEntity") {
		return new CircleEntity();
	} 
	else if (class_name == "Player") {
		return new Player();
	}
	else if (class_name == "Enemy") {
		return new Enemy();
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
