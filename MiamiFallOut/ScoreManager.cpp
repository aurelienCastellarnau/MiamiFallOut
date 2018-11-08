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

void ScoreManager::Update()
{
	for (AbstractEntity* const& it : _entities)
	{
		sf::Shape* shape1 = it->GetShape();
		sf::FloatRect bounds1 = shape1->getGlobalBounds();
		for (AbstractEntity* const& in_it : _entities)
		{
			if (it->GetEntityType() != in_it->GetEntityType()) {
				sf::Shape* shape2 = in_it->GetShape();
				sf::FloatRect bounds2 = shape2->getGlobalBounds(); 
				if(bounds1.intersects(bounds2)) {
				}
			}
		}
	}
}

// IObserver implementation
void ScoreManager::Notify(IObservable *observable)
{
	for (AbstractEntity* const& it : _entities)
	{
		std::cout << "Entity type:" << it->GetEntityType();
	}
	observable->OnNotify();
	return;
}

ScoreManager::~ScoreManager()
{
}
