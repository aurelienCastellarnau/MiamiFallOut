#pragma once
#include "stdafx.h"
#include "AbstractEntity.hh"
#include "IShapeManager.hh"
#include "IObserver.hh"

class ScoreManager: public IObserver, public IShapeManager
{
public:
	ScoreManager();
	ScoreManager(sf::RenderWindow*);

	std::list<AbstractEntity*> GetEntities() const;
	void AddEntity(AbstractEntity* const entity);
	void RemoveEntity(AbstractEntity* const entity);
	void Update();

	// IShapeManager implementation
	void SetWindow(sf::RenderWindow*) override;
	sf::RenderWindow* GetWindow() const override;

	// IObserver implementation
	virtual void Notify(IObservable* observable) override;
	void buildBackround();

	~ScoreManager();

private:

	std::list<AbstractEntity*> _entities;
	sf::RenderWindow* _window;
};
