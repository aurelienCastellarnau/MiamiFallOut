#pragma once
#include "CircleEntity.hh"

class Player : public CircleEntity
{
public:
	Player();
	~Player();
	virtual void Move() override;
	virtual void Draw(IShapeManager*) override;

private:
	sf::Image _playerImage;
	sf::Texture _playerTexture;
	sf::Sprite _playerSprite;
};

