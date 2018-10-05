#include "stdafx.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "Scene.hh"
#include "TimeManager.hh"
#include "ShapeEntity.hh"


Scene::Scene()
{
}

std::list<AbstractEntity*> Scene::GetEntities() const
{
	return _entities;
}

void Scene::AddEntity(AbstractEntity* const entity)
{
	_entities.push_front(entity);
}

void Scene::RemoveEntity(AbstractEntity* const entity)
{
	_entities.remove(entity);
}

void Scene::Update()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
	}
	_window->clear();
	TimeManager& tm = TimeManager::GetInstance();
	tm.Update();
	for (AbstractEntity* const& it: _entities)
	{
		it->Update();
		it->Draw(this);
	}
	_window->display();
}

void Scene::SetWindow(sf::RenderWindow* w)
{
	_window = w;
}

sf::RenderWindow* Scene::GetWindow() const
{
	return _window;
}

Scene::~Scene()
{
}
