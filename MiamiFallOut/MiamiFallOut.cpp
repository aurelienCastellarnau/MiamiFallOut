// MiamiFallOut.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Scene.hh"
#include <SFML/Graphics.hpp>
#include "EntityFactory.hh"
#include "TimeManager.hh"
#include "CircleEntity.hh"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Miami Fall Out !");
	EntityFactory* factory = new EntityFactory();

	TimeManager& tm = TimeManager::GetInstance();
	
	Scene* scene = new Scene();
	CircleEntity* circle = dynamic_cast<CircleEntity*>(factory->Create("CircleEntity"));
	circle->SetCircle(100.f, 30, sf::Color::Cyan);
	
	scene->SetWindow(&window);
	scene->AddEntity(circle);
	tm.Start();
	while (scene->GetWindow()->isOpen())
	{
		tm.Update();
		unsigned int elapsedTime = tm.GetStartedTime();
		if (elapsedTime > 60) {
			tm.Start();
			std::cout << "FPS: " << elapsedTime;
			scene->Update();
		}
	}
	return 0;
}
