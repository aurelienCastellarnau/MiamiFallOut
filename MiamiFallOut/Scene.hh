#pragma once
#include <list>
#include "AbstractEntity.hh"
#include "IShapeManager.hh"

class Scene : IShapeManager
{
public:
	Scene();

	std::list<AbstractEntity*> GetEntities() const;
	void AddEntity(AbstractEntity* const entity);
	void RemoveEntity(AbstractEntity* const entity);
	void Update();

	void SetWindow(sf::RenderWindow*);
	sf::RenderWindow* GetWindow() const;

	~Scene();

private:
	std::list<AbstractEntity*> _entities;
	sf::RenderWindow* _window;
};
