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

int GameManager::GetScore() const
{
	return _score;
}

void GameManager::SetScore(int score)
{
	_score = score;
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
	MenuLoop(&window, true);
}

void GameManager::MenuLoop(sf::RenderWindow* window, bool restart) {
	std::cout << "menu loop";
	if (restart == true) {
		_gameStarted = false;
		this->_scene = new Scene(window);
		this->_scene->PrepareFontMenu();

		while (this->_scene->GetWindow()->isOpen() && _gameStarted == false)
		{
			while (this->_scene->GetWindow()->pollEvent(this->_event))
			{
				if (this->_event.type == sf::Event::Closed || (this->_event.KeyPressed && this->_event.key.code == sf::Keyboard::Escape)) 
				{
					this->_scene->GetWindow()->close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					_gameStarted = true;
				}
			}
			this->_scene->GetWindow()->clear();
			this->_scene->DrawMenu();
			this->_scene->GetWindow()->display();
		}
		if (_gameStarted == true) {
			std::cout << "start game loop from menu loop";
			this->GameLoop();
		}
	}
}

Player* GameManager::GetPlayer() const
{
	return _scene->GetPlayer();
}

void GameManager::SetWindow(sf::RenderWindow* win)
{
	_win = win;
}

void GameManager::GameLoop() {
		EntityFactory *factory = new EntityFactory();
		sf::RenderWindow* window_ptr = _scene->GetWindow();

		// La scene porte la window et observe les entitées
		_score_manager = new ScoreManager(window_ptr);
		Player *player = dynamic_cast<Player*>(factory->Create("Player"));
		Enemy *enemy = dynamic_cast<Enemy*>(factory->Create("Enemy"));
		// settle obersver pattern
		player->AddObserver(_scene);
		enemy->AddObserver(_scene);
		_scene->AddEntity(player);
		_scene->AddEntity(enemy);
		// settle font and text for FPS display
		std::string stringFPS = "";
		_font.loadFromFile("asset/OpenSans-ExtraBold.ttf");
		_textFPS.setFont(_font);
		_textFPS.setCharacterSize(24);
		_textFPS.setFillColor(sf::Color::Red);
		std::string score_str = "";
		_textScore.setFont(_font);
		_textScore.setCharacterSize(35);
		_textScore.setFillColor(sf::Color::White);
		// Start timer
		_score_manager->AddEntity(player);
		_score_manager->AddEntity(enemy);
		sf::Mouse::setPosition(sf::Vector2i(0, 0));

		//init one TimeManager
		_tm = new TimeManager();;
		_tm->Start();
		int count = 0;
		int frames_update = 0;
		// set the probabilities for enemy to pop
		int pop_boundary = 1;

		while (window_ptr->isOpen() && !_score_manager->GetEndCondition())
		{
			if (_event.type == sf::Event::Closed || (_event.KeyPressed && _event.key.code == sf::Keyboard::Escape))
				MenuLoop(window_ptr, true);
			_tm->Update();
			if (player != NULL && _tm->GetStartedTime() > ELAPSED_TIME_FPS) {
				// 100 FPS, toute les 30 secondes, on augmente les chances de pop
				if (frames_update == 3000)
				{
					frames_update = 0;
					pop_boundary++;
					if (pop_boundary > 100)
					{
						pop_boundary = 100;
					}
				}
				frames_update++;
				int pop = GetRandomInt(1, 100);
				if (pop > 0 && pop <= pop_boundary)
				{
					Enemy* new_ennemi = dynamic_cast<Enemy*>(factory->Create("Enemy"));
					new_ennemi->AddObserver(_scene);
					_scene->AddEntity(new_ennemi);
					_score_manager->AddEntity(new_ennemi);
				}
				window_ptr->clear();
				_scene->buildBackround();
				_scene->Update();
				Player* player = GetPlayer();
				if (player != NULL && player->IsCatched())
				{
					_score_manager->SetEndCondition(true);
					player->RemoveObserver(_scene);
					player->RemoveObserver(_score_manager);
					_scene->RemoveEntity(player);
					_score_manager->RemoveEntity(player);
					delete player;
					delete _scene;
				}
				else if (player != NULL) {
					for (ShapeEntity* it : _scene->GetEntities())
					{
						if (it != NULL && !it->isPlayer() && it->GetIntersect())
						{
							_score_manager->SetScore(_score_manager->GetScore() + 1);
							it->RemoveObserver(_scene);
							it->RemoveObserver(_score_manager);
							_scene->RemoveEntity(it);
							_score_manager->RemoveEntity(it);
							delete it;
							continue;
						}
						if (it != NULL)
						{
							it->Move();
							window_ptr->draw(*(it->GetShape()));
						}
					}
				}
				if (count == 8) {
					stringFPS = std::to_string(1000 / _tm->GetStartedTime()) + " FPS";
					_textFPS.setString(stringFPS);
					count = 0;
				}
				_score_manager->Update();
				score_str = "Score: " + std::to_string(_score_manager->GetScore()) + " shots";
				_textScore.setString(score_str);
				window_ptr->draw(_textScore);
				window_ptr->draw(_textFPS);
				window_ptr->display();
				_tm->Start();
				count++;
			}
		}
		MenuLoop(window_ptr, _score_manager->GetEndCondition());
}


unsigned int GameManager::GetRandomInt(int a, int b)
{
	return rand() % (b - a) + a;
}