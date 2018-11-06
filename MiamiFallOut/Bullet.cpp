#include "stdafx.h"
#include "Bullet.hh"
#include <math.h>

Bullet::Bullet()
{
}



Bullet::Bullet(Player player)
{
	this->SetCircle(5, 100, sf::Color(255, 255, 255, 255));
	float radius = this->GetCircle()->getRadius();
	this->GetCircle()->setOrigin(sf::Vector2f(this->GetCircle()->getRadius(), this->GetCircle()->getRadius()));

	float rotation = player.GetCircle()->getRotation();
	
	/*this->SetX((WINDOW_WIDTH / 2));
	this->SetY((WINDOW_HEIGHT));
	
	this->SetCoordonates();
	Scene &scene = *(GameManager::GetInstance().GetScene());
	this->AddObserver(&scene);
	GameManager::GetInstance().GetScene()->AddEntity(this);
	_playerTexture.loadFromFile("../asset/player_big.png", sf::IntRect(0, 0, 60, 60));
	_playerTexture.setSmooth(true);
	this->GetCircle()->setTexture(&_playerTexture, false);*/
}


Bullet::~Bullet()
{
}

void Bullet::GetBulletDirection()
{
}

void Bullet::CalculateAndSetAxe(int rotation)
{
	rotation %= 360;
	
	if (rotation < 0) {
		rotation = 360 - rotation;
	}

	if (rotation == 0) {
		_coeffX = 0.00;
		_coeffY = -1.00f;
	}
	if (rotation > 0 && rotation < 90) {
		_coeffX = sin(rotation);
		_coeffY = cos(rotation) - 1.000000f;
	}
	else if (rotation == 90) {
		_coeffX = 1.00f;
		_coeffY = 0.00f;
	}
	else if (rotation > 90 && rotation < 180) {
		_coeffX = sin(rotation);
		_coeffY = abs(cos(rotation)) ;
	}
	else if (rotation == 180) {
		_coeffX = 0.00f;
		_coeffY = 1.00f;
	}
	else if (rotation > 180 && rotation < 270) {
		_coeffX = sin(rotation);
		_coeffY = abs(cos(rotation));
	}
	else if (rotation == 270) {
		_coeffX = -1.00f;
		_coeffY = 0.00f;
	} else  {
		_coeffX = sin(rotation);
		_coeffY = cos(rotation) * -1.000000f;;
	}
}

void Bullet::Move()
{
}

double Bullet::GetCoeffX()
{
	return _coeffX;
}

void Bullet::SetCoeffX(double coeff)
{
	_coeffX = coeff;
}

double Bullet::GetCoeffY()
{
	return _coeffY;
}

void Bullet::SetCoeffY(double coeff)
{
	_coeffY = coeff;
}

int Bullet::GetAxe()
{
	return _axe;
}

void Bullet::SetAxe(int axe)
{
	_axe = axe;
}

int Bullet::GetSpeed()
{
	return _speed;
}

void Bullet::SetSpeed(int speed)
{
	_speed = speed;
}
