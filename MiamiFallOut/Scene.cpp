#include "stdafx.h"
#include "Scene.hh"
#include "TimeManager.hh"
#include "ShapeEntity.hh"
#include "GameManager.hh"

Scene::Scene() {}

Scene::Scene(sf::RenderWindow* window)
{
	_window = window;
	_bg_image.loadFromFile("../asset/beach.png");
}

void Scene::buildBackround()
{
 	_bg_texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	_bg_texture.update(_bg_image);
	_bg_sprite.setTexture(_bg_texture);
	_window->draw(_bg_sprite);
}

std::list<AbstractEntity*> Scene::GetEntities() const
{
	return _entities;
}

void Scene::AddEntity(AbstractEntity* const entity)
{
	_entities.push_back(entity);
}

void Scene::RemoveEntity(AbstractEntity* const entity)
{
	_entities.remove(entity);
}

void Scene::Update()
{
}

void Scene::SetWindow(sf::RenderWindow* w)
{
	_window = w;
}

sf::RenderWindow* Scene::GetWindow() const
{
	return _window;
}

// IObserver implementation
void Scene::Notify(IObservable *observable)
{
	std::cout << "\nCall notify on Scene";
	this->Update();
	observable->OnNotify();
	return;
}

Scene::~Scene()
{
}
