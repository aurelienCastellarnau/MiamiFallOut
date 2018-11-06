#include "stdafx.h"
#include "time.h"
#include "GameManager.hh"
#include "EntityFactory.hh"
#include "TimeManager.hh"
#include "CircleEntity.hh"
#include "Player.hh"
#include "Enemy.hh"

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

void GameManager::GameStart() {
	
}


void GameManager::GameLoop() {
	if (_init == false) {
		_init = true;
		EntityFactory *factory = new EntityFactory();

		// sf objects
		sf::Event event;
		sf::Mouse::setPosition(sf::Vector2i(0, 0));
		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Miami Fall Out !");
		
		// Observers
		Scene* scene = new Scene(&window);
		_scene->GetWindow()->clear();
		_scene->buildBackround();
		ScoreManager* score_manager = new ScoreManager(&window);

		// La scene porte la window et observe les entitées
		this->SetScene(scene);
		Player *player = dynamic_cast<Player*>(factory->Create("Player"));
		Enemy *enemy = dynamic_cast<Enemy*>(factory->Create("Enemy"));

		// Start timer
		TimeManager& tm = TimeManager::GetInstance();

		// settle observer pattern
		// scene
		_scene->AddEntity(enemy);
		_scene->AddEntity(player);
		player->AddObserver(_scene);
		enemy->AddObserver(_scene);
		// score manager
		_score_manager->AddEntity(player);
		_score_manager->AddEntity(enemy);
		player->AddObserver(_score_manager);
		enemy->AddObserver(_score_manager);

		tm.Start();
		
		while (this->GetScene()->GetWindow()->isOpen())
		{
			while (GetScene()->GetWindow()->pollEvent(event))
			{
				if (event.type == sf::Event::Closed || (event.KeyPressed && event.key.code == sf::Keyboard::Escape))
					GetScene()->GetWindow()->close();
			}
			// Boucle de jeu avec frames réglées sur 60...
			// Tout se fait au travers du pattern observer,
			// changer x ou y déclenche l'update de la scene
			// elle reconstruit son background et redessine
			// le cercle...		

			tm.Update();
			unsigned int elapsedTime = tm.GetStartedTime();

			GetScene()->GetWindow()->clear();
			GetScene()->buildBackround();
			_scene->Update();
			_score_manager->Update();
			GetScene()->GetWindow()->display();

			if (elapsedTime > 60) {
				tm.Start();
				//std::cout << "\nFPS: " << elapsedTime;
				for (ShapeEntity* const& it : _scene->GetEntities())
				{
					it->Move();
					_scene->GetWindow()->draw(*(it->GetShape()));
				}
				GetScene()->GetWindow()->display();
			}
		}
	}
}
