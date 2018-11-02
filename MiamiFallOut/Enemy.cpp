#include "stdafx.h"
#include "Enemy.hh"
#include "GameManager.hh"
#include "TimeManager.hh"

Enemy::Enemy()
{
	int widthAndHeight = TimeManager::GetInstance().GetRandomInt(30, 100);
	this->SetRectangle(
		widthAndHeight,
		widthAndHeight,
		sf::Color(TimeManager::GetInstance().GetRandomInt(0, 255), TimeManager::GetInstance().GetRandomInt(0, 255), TimeManager::GetInstance().GetRandomInt(0, 255), 255));
	float width = this->GetRectangle()->getLocalBounds().width;
	this->SetX(TimeManager::GetInstance().GetRandomInt(0, WINDOW_WIDTH - widthAndHeight));
	this->SetY(0);
	this->SetCoordonates();
	Scene &scene = *(GameManager::GetInstance().GetScene());
	this->AddObserver(&scene);
	GameManager::GetInstance().GetScene()->AddEntity(this);
}


Enemy::~Enemy()
{
}
