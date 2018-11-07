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
	srand(time(NULL));
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

void GameManager::GameStart() {
	
}


void GameManager::GameLoop() {
	if (_init == false) {
		_init = true;
		EntityFactory *factory = new EntityFactory();
		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Miami Fall Out !");
		_scene = new Scene(&window);

		// La scene porte la window et observe les entitées
		_score_manager = new ScoreManager(&window);
		Player *player = dynamic_cast<Player*>(factory->Create("Player"));
		Enemy *enemy = dynamic_cast<Enemy*>(factory->Create("Enemy"));
		// settle obersver pattern
		player->AddObserver(this->_scene);
		this->_scene->AddEntity(player);
		enemy->AddObserver(this->_scene);
		this->_scene->AddEntity(enemy);
		// settle font and text for FPS display
		_fontFPS.loadFromFile("../asset/OpenSans-ExtraBold.ttf");
		_textFPS.setFont(_fontFPS);
		_textFPS.setCharacterSize(24);
		_textFPS.setFillColor(sf::Color::Red);
		// Start timer
		_score_manager->AddEntity(player);
		_score_manager->AddEntity(enemy);
		sf::Event event;
		sf::Mouse::setPosition(sf::Vector2i(0, 0));

		//init one TimeManager
		_tm = new TimeManager();;
		_tm->Start();
		std::string stringFPS = "";
		int count = 0;
		while (_scene->GetWindow()->isOpen())
		{

			while (_scene->GetWindow()->pollEvent(event))
			{
				if (event.type == sf::Event::Closed || (event.KeyPressed && event.key.code == sf::Keyboard::Escape))
					_scene->GetWindow()->close();
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
					// it->Draw(GetScene());
					// it->Update();
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

			/*
			std::cout << "\nFPS: " << elapsedTime;
			for (AbstractEntity* const& it : GetScene()->GetEntities())
			{
			it->Move();
			it->Draw(GetScene());
			it->Update();
			}

			GetScene()->GetWindow()->display();
			}
			*/
		}
	}
}

unsigned int GameManager::GetRandomInt(int a, int b)
{
	return rand() % (b - a) + a;
}

