#pragma once
#include "CircleEntity.hh"
#include "Bullet.hh"
#include "TimeManager.hh"


class Bullet;
class TimeManager;
class Player : public CircleEntity
{
public:
	Player();
	~Player();
	virtual void Move() override;
	//virtual void Draw(sf::RenderWindow*) override;
	void MovePlayerBullets();
	std::list<Bullet*>GetBullets() const;
	void RemoveBullet(Bullet* bullet);
	bool IsCatched() const;

private:
	sf::Image _playerImage;
	sf::Texture _playerTexture;
	sf::Sprite _playerSprite;
	TimeManager* _tm;
	std::list<Bullet*> _bullets;
	const int PLAYER_SPEED = 2;
	const int ROTATION_SPEED = 2;
	const unsigned int DELAY_BULLET = 200;
};

