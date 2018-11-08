#include "stdafx.h"
#include "Player.hh"
#include "CircleEntity.hh"
#include "EntityFactory.hh"
#include "GameManager.hh"
#include "IShapeManager.hh"
#include "ShapeEntity.hh"
#include "Bullet.hh"

Player::Player(): CircleEntity()
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
	_playerTexture.loadFromFile("asset/player_MiamiFallout60x60.png", sf::IntRect(0, 0, 60, 60));
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

int Player::GetBulletSize() const
{
	return _bullets.size();
}

void Player::MovePlayerBullets() {
	if (this->_bullets.size() > 0) {
		for (std::list<Bullet*>::iterator bulletIterator = this->_bullets.begin(); bulletIterator != this->_bullets.end(); bulletIterator++) {
			float coordX = float((*bulletIterator)->GetX() + ((*bulletIterator)->GetCoeffX() * (*bulletIterator)->BULLET_SPEED));
			float coordY = float((*bulletIterator)->GetY() + ((*bulletIterator)->GetCoeffY() * (*bulletIterator)->BULLET_SPEED));
			float bulletHeight = ((*bulletIterator)->GetShape()->getLocalBounds().height);
			float bulletWidth = ((*bulletIterator)->GetShape()->getLocalBounds().width);
			if (coordX < bulletWidth / 2 ||
				coordX + (bulletWidth / 2) >= 1600 ||
				coordY < (bulletHeight / 2) ||
				coordY + (bulletHeight / 2) >= 800 ) {
				if (this->_bullets.size() == 1 || bulletIterator == this->_bullets.end()) {
					this->_bullets.erase(bulletIterator);
					break;
				}
				else if (bulletIterator == this->_bullets.begin()) {
					this->_bullets.erase(bulletIterator);
					MovePlayerBullets();
					break;
				}
				else {
					std::list<Bullet*>::iterator bulletIteratorBefore = bulletIterator--;
					this->_bullets.erase(bulletIterator);
					bulletIterator = bulletIteratorBefore;
				}
			} else {
				(*bulletIterator)->Move();
			}
		}
	}
};

bool Player::IsCatched() const {
	return this->GetIntersect();
}

std::list<Bullet*> Player::GetBullets() const
{
	return _bullets;
}

void Player::RemoveBullet(Bullet* bullet)
{
	_bullets.remove(bullet);
}
