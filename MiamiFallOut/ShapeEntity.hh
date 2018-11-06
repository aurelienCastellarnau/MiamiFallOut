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

	virtual void Draw(sf::RenderWindow*) override;
	virtual void Update() override;
	virtual std::string& Serialize() override;
	virtual void Move() = 0;

	// IObservable implementation

	virtual void AddObserver(IObserver* observer) override;
	virtual void RemoveObserver(IObserver* observer) override;
	virtual void OnNotify() override;

	// ShapeEntity definition
	ShapeEntity();
	virtual ~ShapeEntity() = 0;

	virtual std::string GetEntityType() const override;
	virtual sf::Shape* GetShape() const override;
	virtual void SetShape(sf::Shape*);

	virtual double GetX() const;
	virtual double GetY() const;
	virtual void SetEntityType(std::string type) override;
	virtual void SetX(double x);
	virtual void SetY(double y);
	virtual void SetCoordonates();

private:
	double _x;
	double _y;
	sf::Shape* _shape;
	std::string _entity_type;
	std::list<IObserver*> _observers;
};

