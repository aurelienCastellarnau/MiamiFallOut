#pragma once
#include "stdafx.h"
#include "ShapeEntity.hh"
#include "Player.hh"
#include "IShapeManager.hh"
#include "IObserver.hh"

class Scene : public IShapeManager, public IObserver
{
public:

	// Scene implémentation 
	Scene();
	Scene(sf::RenderWindow*);
	
	std::list<ShapeEntity*> GetEntities() const;
	Player* GetPlayer() const;
	void AddEntity(ShapeEntity* const entity);
	void RemoveEntity(ShapeEntity* const entity);
	void Update();

	// IShapeManager implementation
	void SetWindow(sf::RenderWindow*) override;
	sf::RenderWindow* GetWindow() const override;
	
	// IObserver implementation
	virtual void Notify(IObservable* observable) override;
	void buildBackround();

	void PrepareFontMenu();

	void DrawMenu();

	~Scene();

private:

	std::list<ShapeEntity*> _entities;
	sf::RenderWindow* _window;
	sf::Image _bg_image;
	sf::Texture _bg_texture;
	sf::Sprite _bg_sprite;
	sf::Text _textWelcome;
	sf::Text _textQuitOrBegin;
	sf::Text _textHelpTip;
	sf::Text _textScore;
	sf::Text _textLolCage;
	std::string _stringMenu;
	std::string _stringQuitOrBegin;
	std::string _stringHelpTip;
	std::string _stringLolCage;
	std::string _score;
	sf::Font _fontMenu;
	sf::Font _lolFontMenu;

};
