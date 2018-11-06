#include "stdafx.h"
#include "ScoreManager.hh"
#include "TimeManager.hh"
#include "ShapeEntity.hh"
#include "GameManager.hh"

ScoreManager::ScoreManager() {}

ScoreManager::ScoreManager(sf::RenderWindow* window)
{
	_window = window;
}

void ScoreManager::SetWindow(sf::RenderWindow* w)
{
	_window = w;
}

sf::RenderWindow* ScoreManager::GetWindow() const
{
	return _window;
}

std::list<AbstractEntity*> ScoreManager::GetEntities() const
{
	return _entities;
}

void ScoreManager::AddEntity(AbstractEntity* const entity)
{
	_entities.push_back(entity);
}

void ScoreManager::RemoveEntity(AbstractEntity* const entity)
{
	_entities.remove(entity);
}

// IObserver implementation
void ScoreManager::Notify(IObservable *observable)
{
	std::cout << "\nCall notify on Scene";
	this->Update();
	observable->OnNotify();
	return;
}

ScoreManager::~ScoreManager()
{
}
