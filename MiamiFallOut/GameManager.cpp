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
/*
	
*/
int GameManager::GetScore() const
{
	return _score;
}

void GameManager::SetScore(int score)
{
	_score = score;
}

void GameManager::setScene(Scene *scene) {
	this->_scene = scene;
}

Scene* GameManager::GetScene() const {
	return this->_scene;
}



void GameManager::GameStart()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Miami Fall Out !");
	menuLoop(&window, true);
}

void GameManager::settleText()
{
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
}

void GameManager::settleObserverPlayer(Player* player)
{
	// settle obersver pattern
	player->AddObserver(_scene);
	_scene->AddEntity(player);
	_score_manager->AddEntity(player);
}

void GameManager::settleObserverEnemy(Enemy* enemy)
{
	// settle obersver pattern
	enemy->AddObserver(_scene);
	_scene->AddEntity(enemy);
	_score_manager->AddEntity(enemy);
}

// remove layer from observers, delete player and _scene
void GameManager::playerIsCatched(Player* player)
{
	_score_manager->SetEndCondition(true);
	player->RemoveObserver(_scene);
	player->RemoveObserver(_score_manager);
	_scene->RemoveEntity(player);
	_score_manager->RemoveEntity(player);
	delete player;
	delete _scene;
}

void GameManager::checkEnemiesHit()
{
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
			_scene->GetWindow()->draw(*(it->GetShape()));
		}
	}
}

int GameManager::enemyPoper(int pop_boundary)
{
	static int frames_update;
	EntityFactory *factory = new EntityFactory();
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
		Enemy* new_enemy = dynamic_cast<Enemy*>(factory->Create("Enemy"));
		settleObserverEnemy(new_enemy);
	}
	return pop_boundary;
}


void GameManager::menuLoop(sf::RenderWindow* window, bool restart) {
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
			this->gameLoop();
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

void GameManager::makeAFrame(sf::RenderWindow* window_ptr)
{
	static int count = 0;

	// retrieve the player or NULL
	Player* player = GetPlayer();
	// check player defeat
	if (player->IsCatched())
	{
		// remove player, delete player and _scene
		playerIsCatched(player);
	}
	else {
		// remove killed enemies
		checkEnemiesHit();
	}
	if (count == 8) {
		_textFPS.setString(std::to_string(1000 / _tm->GetStartedTime()) + " FPS");
		count = 0;
	}
	_textScore.setString("Score: " + std::to_string(_score_manager->GetScore()) + " shots");
	window_ptr->draw(_textScore);
	window_ptr->draw(_textFPS);
	window_ptr->display();
	_tm->Start();
	count++;
}

void GameManager::gameLoop() {
	// 
	EntityFactory *factory = new EntityFactory();
	sf::RenderWindow* window_ptr = _scene->GetWindow();

	// La scene porte la window et observe les entitées
	_score_manager = new ScoreManager(window_ptr);
	Player *player = dynamic_cast<Player*>(factory->Create("Player"));
	Enemy *enemy = dynamic_cast<Enemy*>(factory->Create("Enemy"));
	// settle text parts
	settleText();
	settleObserverPlayer(player);
	settleObserverEnemy(enemy);

	// ?
	sf::Mouse::setPosition(sf::Vector2i(0, 0));

	//init one TimeManager
	_tm = new TimeManager();;
	_tm->Start();
	// usefull counters for fps display and difficulty ennemys pop
	int count = 0;
	// set the probabilities for enemy to pop
	int pop_boundary = 1;
	while (window_ptr->isOpen() && !_score_manager->GetEndCondition())
	{
		if (_event.type == sf::Event::Closed || (_event.KeyPressed && _event.key.code == sf::Keyboard::Escape))
			menuLoop(window_ptr, true);
		_tm->Update();
		if ( _tm->GetStartedTime() > ELAPSED_TIME_FPS) {
			// on fait poper aléatoirement des méchants
			pop_boundary = enemyPoper(pop_boundary);
			// window rebuild
			window_ptr->clear();
			_scene->buildBackround();
			if (player != NULL)
			{
				makeAFrame(window_ptr);
				// Observers update
				_scene->Update();
				_score_manager->Update();
			}
		}
	}
	menuLoop(window_ptr, _score_manager->GetEndCondition());
}


unsigned int GameManager::GetRandomInt(int a, int b)
{
	return rand() % (b - a) + a;
}