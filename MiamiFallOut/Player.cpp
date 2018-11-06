#include "stdafx.h"
#include "Player.hh"
#include "CircleEntity.hh"
#include "EntityFactory.hh"
#include "GameManager.hh"
#include "IShapeManager.hh"
#include "ShapeEntity.hh"
#include "Bullet.hh"

Player::Player()
{
	this->SetCircle(30.0f, 100, sf::Color(255,255,255,255));
	float radius = this->GetCircle()->getRadius();
	this->GetCircle()->setOrigin(sf::Vector2f(this->GetCircle()->getRadius(), this->GetCircle()->getRadius()));
	this->SetX((WINDOW_WIDTH / 2));
	this->SetY((WINDOW_HEIGHT));
	this->SetCoordonates();
	Scene &scene = *(GameManager::GetInstance().GetScene());
	//this->AddObserver(&scene);
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
	/*if (this->bullet) {
		this->bullet->Move();
		window->draw(*(bullet->GetShape()));
	}*/
}


void Player::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->SetY(this->GetY() + PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		this->SetY(this->GetY() - PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->SetX(this->GetX() - PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->SetX(this->GetX() + PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->GetCircle()->setRotation(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->GetCircle()->rotate(180);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->GetCircle()->rotate(5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->GetCircle()->rotate(-5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->bullet = new Bullet(this);
	}
	this->SetCoordonates();
}