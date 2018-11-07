#pragma once
#include "CircleEntity.hh"
#include "Player.hh"

class Player;
class Bullet : public CircleEntity
{
public:
	Bullet();
	Bullet(Player* player);
	~Bullet();

	void GetBulletDirection();
	void CalculateAndSetAxe(int rotation);
	virtual void Move() override;

	double GetAxe();
	void SetAxe(double Axe);

	double GetCoeffX();
	void SetCoeffX(double coeff);

	double GetCoeffY();
	void SetCoeffY(double coeff);

private:
	double _axe;
	double _coeffX;
	double _coeffY;
	const int BULLET_SPEED = 1;
};
