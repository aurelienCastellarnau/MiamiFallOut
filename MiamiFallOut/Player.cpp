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
	this->SetEntityType("player");
	this->SetCircle(30.0f, 100, sf::Color(255,255,255,255));
	float radius = this->GetCircle()->getRadius();
	this->GetCircle()->setOrigin(sf::Vector2f(this->GetCircle()->getRadius(), this->GetCircle()->getRadius()));
	this->SetX((WINDOW_WIDTH / 2));
	this->SetY((WINDOW_HEIGHT));
	this->SetCoordonates();
	Scene &scene = *(GameManager::GetInstance().GetScene());
	this->AddObserver(&scene);
	GameManager::GetInstance().GetScene()->AddEntity(this);
	_playerTexture.loadFromFile("../asset/player_MiamiFallout60x60.png", sf::IntRect(0, 0, 60, 60));
	_playerTexture.setSmooth(true);
	this->GetCircle()->setTexture(&_playerTexture, false);
	_tm = new TimeManager();
	_tm->Start();
	_tm->Update();
}


Player::~Player()
{

}

/*void Player::Draw(sf::RenderWindow* window) {
	sf::Shape* s = GetShape();
	window->draw(*s);
	if (this->bullet) {
		this->bullet->Move();
		window->draw(*(bullet->GetShape()));
	}
}*/


void Player::Move()
{
	_tm->Update();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _tm->GetStartedTime() > DELAY_BULLET) {
		this->_bullets.push_back(new Bullet(this));
		_tm->Start();
	}
	this->SetCoordonates();
	this->MovePlayerBullets();
}

void Player::MovePlayerBullets() {
	if (this->_bullets.size() > 0) {
		std::cout << "NB_BULLET " << _bullets.size();
		for (Bullet *bulletIterator : _bullets) {
			if (float(bulletIterator->GetX() + (bulletIterator->GetCoeffX() * bulletIterator->BULLET_SPEED) + (bulletIterator->GetShape()->getLocalBounds().width / 2)) >= 1600
				|| float(bulletIterator->GetX() + (bulletIterator->GetCoeffX() * bulletIterator->BULLET_SPEED) + (bulletIterator->GetShape()->getGlobalBounds().height / 2)) >= 800) {

				this->_bullets.remove(bulletIterator);
				continue;
			}
			else {
				bulletIterator->Move();		
				bulletIterator++;
			}
		}
	}
};
