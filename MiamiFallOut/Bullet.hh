#pragma once
#include "CircleEntity.hh"
#include "Player.hh"

class Bullet : public CircleEntity
{
public:
	Bullet();
	Bullet(Player player);
	~Bullet();

	void GetBulletDirection();
	void CalculateAndSetAxe(int rotation);
	virtual void Move() override;

	int GetAxe();
	void SetAxe(int Axe);

	double GetCoeffX();
	void SetCoeffX(double coeff);

	double GetCoeffY();
	void SetCoeffY(double coeff);

	int GetSpeed();
	void SetSpeed(int speed);

private:
	int _axe;
	double _coeffX;
	double _coeffY;
	int _speed;
	
};

