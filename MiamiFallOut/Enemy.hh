#pragma once
#include "RectangleEntity.hh"
class Enemy : public RectangleEntity
{
public:
	Enemy();
	virtual void Move() override;
	~Enemy();
private:
	sf::Texture _enemyTexture;
	const int ENEMY_SPEED = 4;
};

