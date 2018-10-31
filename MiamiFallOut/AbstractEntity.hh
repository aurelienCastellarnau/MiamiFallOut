#pragma once
#include "ISerialize.hh"
#include "IShapeManager.hh"

class AbstractEntity: ISerialize
{
public:
	AbstractEntity();
	virtual ~AbstractEntity();

	virtual void Draw(IShapeManager*) = 0;
	virtual void Update() = 0;
	virtual void Move() = 0;
	virtual std::string& Serialize() = 0;
};
