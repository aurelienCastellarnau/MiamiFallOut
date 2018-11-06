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

		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Miami Fall Out !");
		Scene* scene = new Scene(&window);
		ScoreManager* score_manager = new ScoreManager(&window);
		// La scene porte la window et observe les entitées
		this->SetScene(scene);
		_score_manager = new ScoreManager(&window);
		Player *player = dynamic_cast<Player*>(factory->Create("Player"));
		Enemy *enemy = dynamic_cast<Enemy*>(factory->Create("Enemy"));
		// settle obersver pattern
		player->AddObserver(this->_scene);
		this->_scene->AddEntity(player);
		enemy->AddObserver(this->_scene);
		this->_scene->AddEntity(enemy);
		// Start timer
		_score_manager->AddEntity(player);
		_score_manager->AddEntity(enemy);
		TimeManager::GetInstance().Start();
		sf::Event event;
		sf::Mouse::setPosition(sf::Vector2i(0, 0));

		_scene->GetWindow()->clear();
		_scene->buildBackround();
		TimeManager::GetInstance().Start();
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

			TimeManager& tm = TimeManager::GetInstance();
			tm.Update();
			TimeManager::GetInstance().Update();
			unsigned int elapsedTime = TimeManager::GetInstance().GetStartedTime();

			GetScene()->GetWindow()->clear();
			GetScene()->buildBackround();
			_scene->Update();
			_score_manager->Update();
			GetScene()->GetWindow()->display();

			if (elapsedTime > 60) {
				TimeManager::GetInstance().Start();
				//std::cout << "\nFPS: " << elapsedTime;
				for (ShapeEntity* const& it : _scene->GetEntities())
				{
					it->Move();
					_scene->GetWindow()->draw(*(it->GetShape()));
					// it->Draw(GetScene());
					// it->Update();
				}
				GetScene()->GetWindow()->display();
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
