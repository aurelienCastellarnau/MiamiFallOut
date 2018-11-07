#pragma once
#include "stdafx.h"
#include "ShapeEntity.hh"
#include "IShapeManager.hh"
#include "IObserver.hh"

class Scene : public IShapeManager, public IObserver
{
public:

	// Scene implémentation 
	Scene();
	Scene(sf::RenderWindow*);
	
	std::list<ShapeEntity*> GetEntities() const;
	void AddEntity(ShapeEntity* const entity);
	void RemoveEntity(ShapeEntity* const entity);
	void Update();

	// IShapeManager implementation
	void SetWindow(sf::RenderWindow*) override;
	sf::RenderWindow* GetWindow() const override;
	
	// IObserver implementation
	virtual void Notify(IObservable* observable) override;
	void buildBackround();

	~Scene();

private:

	std::list<ShapeEntity*> _entities;
	sf::RenderWindow* _window;
	sf::Image _bg_image;
	sf::Texture _bg_texture;
	sf::Sprite _bg_sprite;
};
