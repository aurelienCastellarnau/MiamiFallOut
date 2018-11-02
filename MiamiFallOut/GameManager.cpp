#include "stdafx.h"
#include "GameManager.hh"
#include "EntityFactory.hh"
#include "TimeManager.hh"
#include "CircleEntity.hh"
#include "Player.hh"

GameManager &GameManager::GetInstance() {
	static GameManager _instance;
	return _instance;
}

GameManager::GameManager()
{
	// Le timer
	if (_init == false) {
		_init = true;
		EntityFactory *factory = new EntityFactory();

		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Miami Fall Out !");
		Scene* scene = new Scene(&window);
		// La scene porte la window et observe les entitées
		this->SetScene(scene);
		Player *player = dynamic_cast<Player*>(factory->Create("Player"));
		player->AddObserver(this->GetScene());
		this->GetScene()->AddEntity(player);
		TimeManager::GetInstance().Start();
		std::cout << "\nKeyboard input constants: " << VK_BACK;

		while (this->GetScene()->GetWindow()->isOpen())
		{
			GameLoop();
		}
	}
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

void GameManager::GameLoop() {
	this->GetScene()->Update();
	// Boucle de jeu avec frames réglées sur 60...
	// Tout se fait au travers du pattern observer,
	// changer x ou y déclenche l'update de la scene
	// elle reconstruit son background et redessine
	// le cercle...		

	TimeManager::GetInstance().Update();
	unsigned int elapsedTime = TimeManager::GetInstance().GetStartedTime();
	this->GetScene()->GetEntities().front()->Move();
	if (elapsedTime > 60) {
		TimeManager::GetInstance().Start();
		std::cout << "\nFPS: " << elapsedTime;
	}

}


