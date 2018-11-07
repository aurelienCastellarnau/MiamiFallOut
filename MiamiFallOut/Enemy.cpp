#include "stdafx.h"
#include "Enemy.hh"
#include "GameManager.hh"
#include "TimeManager.hh"
#include "Player.hh"

Enemy::Enemy()
{
	this->SetEntityType("enemy");
	int widthAndHeight = GameManager::GetInstance().GetRandomInt(30, 150);
	this->SetRectangle(
		widthAndHeight,
		widthAndHeight,
		sf::Color(GameManager::GetInstance().GetRandomInt(0, 255), GameManager::GetInstance().GetRandomInt(0, 255), GameManager::GetInstance().GetRandomInt(0, 255), 255));
	float width = this->GetRectangle()->getLocalBounds().width;
	this->SetX(GameManager::GetInstance().GetRandomInt(0, WINDOW_WIDTH - widthAndHeight));
	this->SetY(0);
	this->SetCoordonates();
	this->GetRectangle()->setOrigin(sf::Vector2f(widthAndHeight / 2 , widthAndHeight / 2));
}

void Enemy::Move() {
	auto scene = GameManager::GetInstance().GetScene();
	auto entities = scene->GetEntities();
	Player *player = dynamic_cast<Player*>(entities.front());
	float pX = player->GetX();
	float pY = player->GetY();
	float thisX = this->GetX();
	float thisY = this->GetY();

	if (abs(thisX - pX) > 0 && abs(thisX - pX) < 3) {
		this->SetX(pX);
	} else if (thisX < pX) {
		this->SetX(thisX + 3);
	}
	else if (thisX > pX) {
		this->SetX(thisX - 3);
	}
	
	if (abs(thisY - pY) > 0 && abs(thisY - pY) < 3) {
		this->SetY(pY);
	} else if (thisY < pY) {
		this->SetY(thisY + 3);
	}
	else if (thisY > pY) {
		this->SetY(thisY - 3);
	}
	this->SetCoordonates();
}

Enemy::~Enemy()
{
}
