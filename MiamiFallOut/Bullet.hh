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
	virtual void Move() override;

	double GetAxe() const;
	void SetAxe(double Axe);

	double GetCoeffX() const;
	void SetCoeffX(double coeff);

	double GetCoeffY() const;
	void SetCoeffY(double coeff);
	const int BULLET_SPEED = 10;

private:
	double _axe;
	double _coeffX;
	double _coeffY;
	void CalculateAndSetAxe(int rotation);
};

