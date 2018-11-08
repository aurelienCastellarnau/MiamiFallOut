#pragma once
#include "stdafx.h"
#include "AbstractEntity.hh"
#include "IShapeManager.hh"
#include "ShapeEntity.hh"
#include "IObserver.hh"
#include "Player.hh"

class ScoreManager: public IObserver, public IShapeManager
{
public:
	ScoreManager();
	ScoreManager(sf::RenderWindow*);

	std::list<ShapeEntity*> GetEntities() const;
	Player* GetPlayer() const;
	void AddEntity(ShapeEntity* const entity);
	void RemoveEntity(ShapeEntity* const entity);
	void Update();

	// IShapeManager implementation
	void SetWindow(sf::RenderWindow*) override;
	sf::RenderWindow* GetWindow() const override;
	bool GetEndCondition() const;
	void SetEndCondition(bool end_condition);
	int GetScore() const;
	void SetScore(int score);
	int GetHit() const;
	void SetHit(int hit);
	// IObserver implementation
	virtual void Notify(IObservable* observable) override;

	~ScoreManager();

private:

	std::list<ShapeEntity*> _entities;
	sf::RenderWindow* _window;
	bool _end_condition;
	int _score;
	int _hit;
};
