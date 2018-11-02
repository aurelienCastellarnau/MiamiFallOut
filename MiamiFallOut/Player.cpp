#include "stdafx.h"
#include "Player.hh"
#include "CircleEntity.hh"
#include "EntityFactory.hh"
#include "GameManager.hh"

Player::Player()
{
	this->SetCircle(30.0f, 100, sf::Color::Cyan);
	float radius = this->GetCircle()->getRadius();
	this->SetX((WINDOW_WIDTH / 2) - radius);
	this->SetY((WINDOW_HEIGHT - radius));
	this->SetCoordonates();
	Scene &scene = *(GameManager::GetInstance().GetScene());
	this->AddObserver(&scene);
	GameManager::GetInstance().GetScene()->AddEntity(this);	
}


Player::~Player()
{
}
