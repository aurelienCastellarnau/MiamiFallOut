#pragma once
#include <list>
#include <SFML/Graphics.hpp>
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
	virtual void AddObserver(IObserver* observer) override;
	virtual void RemoveObserver(IObserver* observer) override;
	virtual std::string& Serialize() override;

	// Character
	ShapeEntity();
	virtual ~ShapeEntity() = 0;

	virtual sf::Shape* GetShape() const;

	virtual void SetShape(sf::Shape*);

private:
	sf::Shape* _shape;
	std::list<IObserver*> _observers;
};

