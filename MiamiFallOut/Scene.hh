#pragma once
#include "stdafx.h"
#include "AbstractEntity.hh"
#include "IShapeManager.hh"
#include "IObserver.hh"

class Scene : public IShapeManager, public IObserver
{
public:

	// Scene implémentation 
	Scene();
	Scene(sf::RenderWindow*);
	
	std::list<AbstractEntity*> GetEntities() const;
	void AddEntity(AbstractEntity* const entity);
	void RemoveEntity(AbstractEntity* const entity);
	void Update();

	// IShapeManager implementation
	void SetWindow(sf::RenderWindow*) override;
	sf::RenderWindow* GetWindow() const override;
	
	// IObserver implementation
	virtual void Notify(IObservable* observable) override;
	
	~Scene();

private:
	void buildBackround();

	std::list<AbstractEntity*> _entities;
	sf::RenderWindow* _window;
	sf::Image _bg_image;
	sf::Texture _bg_texture;
	sf::Sprite _bg_sprite;
};
