#include "stdafx.h"
#include "Player.hh"
#include "CircleEntity.hh"
#include "EntityFactory.hh"
#include "GameManager.hh"

Player::Player()
{
	this->SetCircle(30.0f, 100, sf::Color::Cyan);
	//setting the circle in the middle of the map at the bottom;
	float radius = this->GetCircle()->getRadius();
	this->SetX((WINDOW_WIDTH / 2) - radius);
	this->SetY((WINDOW_HEIGHT - radius));
	// la scene observe le cerlce
	
}


Player::~Player()
{
}
