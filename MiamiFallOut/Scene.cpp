#include "stdafx.h"
#include "Scene.hh"
#include "TimeManager.hh"
#include "ShapeEntity.hh"
#include "GameManager.hh"

Scene::Scene() {}

Scene::Scene(sf::RenderWindow* window)
{
	_window = window;
	_bg_image.loadFromFile("asset/beach.png");
	_bg_texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	_bg_texture.update(_bg_image);
	_bg_sprite.setTexture(_bg_texture);
}

void Scene::buildBackround()
{
	_window->draw(_bg_sprite);
}

void Scene::PrepareFontMenu() {
	this->_fontMenu.loadFromFile("asset/OpenSans-ExtraBold.ttf");
	this->_stringMenu = "WELCOME IN MIAMI FALLOUT";
	this->_stringQuitOrBegin = "Press Space Bar to launch the Game OR press escape to quit.";
	this->_stringHelpTip = "In Game: ZQSD to move, LEFT and RIGHT arrow to rotate, SPACE BAR to shoot";
	this->_score = "";

	this->_textWelcome.setFont(_fontMenu);
	this->_textQuitOrBegin.setFont(_fontMenu);
	this->_textHelpTip.setFont(_fontMenu);
	this->_textScore.setFont(_fontMenu);

	this->_textWelcome.setCharacterSize(80);
	this->_textQuitOrBegin.setCharacterSize(30);
	this->_textHelpTip.setCharacterSize(30);
	this->_textScore.setCharacterSize(30);

	this->_textWelcome.setFillColor(sf::Color(113, 29, 29, 255));
	this->_textQuitOrBegin.setFillColor(sf::Color(156, 27, 27, 255));
	this->_textHelpTip.setFillColor(sf::Color(179, 32, 32, 255));
	this->_textScore.setFillColor(sf::Color(151, 18, 18, 255));

	this->_textWelcome.setPosition(250, 260);
	this->_textQuitOrBegin.setPosition(400, 400);
	this->_textHelpTip.setPosition(280, 450);
	this->_textScore.setPosition(100, 300);

	this->_textWelcome.setString(this->_stringMenu);
	this->_textQuitOrBegin.setString(this->_stringQuitOrBegin);
	this->_textHelpTip.setString(this->_stringHelpTip);
	this->_textScore.setString(this->_score);
}

void Scene::DrawMenu() {
	buildBackround();
	this->_window->draw(this->_textWelcome);
	this->_window->draw(this->_textQuitOrBegin);
	this->_window->draw(this->_textHelpTip);
	if (this->_textScore.getString() != "") {
		this->_window->draw(this->_textScore);
	}
}

std::list<ShapeEntity*> Scene::GetEntities() const
{
	return _entities;
}
 
Player* Scene::GetPlayer() const
{
	for (ShapeEntity* it : _entities)
	{
		if (it->isPlayer())
		{
			Player* player = dynamic_cast<Player*>(it);
			return player;
		}
	}
	return NULL;
}

void Scene::AddEntity(ShapeEntity* const entity)
{
	_entities.push_back(entity);
}

void Scene::RemoveEntity(ShapeEntity* const entity)
{
	_entities.remove(entity);
}

void Scene::Update()
{
	/*
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
	}
	_window->clear();
	buildBackround();
	TimeManager& tm = TimeManager::GetInstance();
	tm.Update();
	for (AbstractEntity* const& it: _entities)
	{
		it->Update();
		_window->draw(*(it->GetShape()));
	}
	*/
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
	/*std::cout << "\nCall notify on Scene";
	this->Update();
	observable->OnNotify();
	return;*/
}

Scene::~Scene()
{
}
