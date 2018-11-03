#pragma once
#include "RectangleEntity.hh"
class Enemy : public RectangleEntity
{
public:
	Enemy();
	virtual void Move() override;
	~Enemy();
};

