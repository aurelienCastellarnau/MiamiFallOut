#pragma once
#include "CircleEntity.hh"
#include "Bullet.hh"

class Bullet;
class Player : public CircleEntity
{
public:
	Player();
	~Player();
	virtual void Move() override;
	//virtual void Draw(sf::RenderWindow*) override;
	Bullet *bullet;

private:
	sf::Image _playerImage;
	sf::Texture _playerTexture;
	sf::Sprite _playerSprite;
	const int PLAYER_SPEED = 1;
	const int ROTATION_SPEED = 5;
};

