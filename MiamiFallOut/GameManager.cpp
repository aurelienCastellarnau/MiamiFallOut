#include "stdafx.h"
#include "time.h"
#include "GameManager.hh"
#include "EntityFactory.hh"
#include "TimeManager.hh"
#include "CircleEntity.hh"
#include "Player.hh"
#include "Enemy.hh"
#include <string> 

GameManager &GameManager::GetInstance() {
	static GameManager _instance;
	return _instance;
}

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}


void GameManager::SetScene(Scene *scene) {
	this->_scene = scene;
}

Scene* GameManager::GetScene() const {
	return this->_scene;
}

void GameManager::GameStart()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Miami Fall Out !");
	MenuLoop(&window);
}

void GameManager::MenuLoop(sf::RenderWindow* window, bool endGame) {
	if (endGame == false) {
		this->_gameStarted = false;
		this->_init = false;
		this->_scene = new Scene(window);
		this->_scene->PrepareFontMenu();


		while (this->_scene->GetWindow()->isOpen() && this->_gameStarted == false)
		{
			while (this->_scene->GetWindow()->pollEvent(this->_event))
			{
				if (this->_event.type == sf::Event::Closed || (this->_event.KeyPressed && this->_event.key.code == sf::Keyboard::Escape)) {
					this->_scene->GetWindow()->close();
					endGame = true;
				}
				if (this->_event.KeyPressed && this->_event.key.code == sf::Keyboard::Space)
					this->_gameStarted = true;
			}
			this->_scene->GetWindow()->clear();
			this->_scene->DrawMenu();
			this->_scene->GetWindow()->display();
		}
		if (endGame == false) {
			this->GameLoop();
		}
	}
}


void GameManager::GameLoop() {
	if (_init == false) {
		bool endGame = false;
		_init = true;
		EntityFactory *factory = new EntityFactory();
		// La scene porte la window et observe les entitées
		_score_manager = new ScoreManager(this->_scene->GetWindow());
		Player *player = dynamic_cast<Player*>(factory->Create("Player"));
		Enemy *enemy = dynamic_cast<Enemy*>(factory->Create("Enemy"));
		// settle obersver pattern
		player->AddObserver(this->_scene);
		this->_scene->AddEntity(player);
		enemy->AddObserver(this->_scene);
		this->_scene->AddEntity(enemy);
		// settle font and text for FPS display
		this->_fontFPS.loadFromFile("asset/OpenSans-ExtraBold.ttf");
		this->_textFPS.setFont(_fontFPS);
		this->_textFPS.setCharacterSize(24);
		this->_textFPS.setFillColor(sf::Color::Red);
		// Start timer
		_score_manager->AddEntity(player);
		_score_manager->AddEntity(enemy);
		sf::Mouse::setPosition(sf::Vector2i(0, 0));

		//init one TimeManager
		_tm = new TimeManager();;
		_tm->Start();
		std::string stringFPS = "";
		int count = 0;
		while (_scene->GetWindow()->isOpen())
		{
			while (_scene->GetWindow()->pollEvent(_event))
			{
				if (_event.type == sf::Event::Closed || (_event.KeyPressed && _event.key.code == sf::Keyboard::Escape)) {
					_scene->GetWindow()->close();
					endGame = true;
				}
			}
			// Boucle de jeu avec frames réglées sur 120...
			// Tout se fait au travers du pattern observer,
			// changer x ou y déclenche l'update de la scene
			// elle reconstruit son background et redessine
			// le cercle...		

			_tm->Update();

			if (_tm->GetStartedTime() > ELAPSED_TIME_FPS) {
				_scene->GetWindow()->clear();
				_scene->buildBackround();
				_scene->Update();
				_score_manager->Update();
				for (ShapeEntity* const& it : _scene->GetEntities())
				{
					it->Move();
					_scene->GetWindow()->draw(*(it->GetShape()));
				}
				if (count == 8) {
					stringFPS = std::to_string(1000 / _tm->GetStartedTime()) + " FPS";
					_textFPS.setString(stringFPS);
					count = 0;
				}
				_scene->GetWindow()->draw(_textFPS);
				_scene->GetWindow()->display();
				_tm->Start();
				count++;
			}
		}
		MenuLoop(GetScene()->GetWindow(), endGame);
	}
}


unsigned int GameManager::GetRandomInt(int a, int b)
{
	return rand() % (b - a) + a;
}