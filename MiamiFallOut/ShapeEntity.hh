#pragma once
#include "stdafx.h"
#include "AbstractEntity.hh"
#include "IObservable.hh"
#include "IObserver.hh"
#include "IShapeManager.hh"

class ShapeEntity :
	public AbstractEntity, IObservable
{
public:
	// AbstractEntity implementation

	virtual void Draw(IShapeManager*) override;
	virtual void Update() override;
	virtual std::string& Serialize() override;

	// IObservable implementation

	virtual void AddObserver(IObserver* observer) override;
	virtual void RemoveObserver(IObserver* observer) override;
	virtual void OnNotify() override;

	// ShapeEntity definition
	ShapeEntity();
	virtual ~ShapeEntity() = 0;

	virtual sf::Shape* GetShape() const;
	virtual void SetShape(sf::Shape*);

	virtual double GetX() const;
	virtual double GetY() const;
	virtual void SetX(double x);
	virtual void SetY(double y);
	virtual void SetCoordonates();

private:
	double _x;
	double _y;
	sf::Shape* _shape;
	std::list<IObserver*> _observers;
};

