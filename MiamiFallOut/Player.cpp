#include "stdafx.h"
#include "Player.hh"
#include "CircleEntity.hh"
#include "EntityFactory.hh"
#include "GameManager.hh"
#include "IShapeManager.hh"
#include "ShapeEntity.hh"

Player::Player()
{
	this->SetCircle(30.0f, 100, sf::Color(255,255,255,255));
	float radius = this->GetCircle()->getRadius();
	this->GetCircle()->setOrigin(sf::Vector2f(this->GetCircle()->getRadius(), this->GetCircle()->getRadius()));
	this->SetX((WINDOW_WIDTH / 2));
	this->SetY((WINDOW_HEIGHT));
	this->SetCoordonates();
	Scene &scene = *(GameManager::GetInstance().GetScene());
	this->AddObserver(&scene);
	GameManager::GetInstance().GetScene()->AddEntity(this);
	_playerTexture.loadFromFile("../asset/player_big.png", sf::IntRect(0, 0, 60, 60));
	_playerTexture.setSmooth(true);
	this->GetCircle()->setTexture(&_playerTexture, false);

}


Player::~Player()
{

}

void Player::Draw(IShapeManager* manager) {
	sf::Shape* s = GetShape();
	sf::RenderWindow* window = manager->GetWindow();
	window->draw(*s);
	window->draw(_playerSprite);
}
