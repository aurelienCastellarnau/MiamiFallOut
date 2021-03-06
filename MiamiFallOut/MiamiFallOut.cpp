// MiamiFallOut.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Scene.hh"
#include <SFML/Graphics.hpp>
#include "EntityFactory.hh"
#include "TimeManager.hh"
#include "CircleEntity.hh"
#include "RectangleEntity.hh"
#include "GameManager.hh"
// dev
#include <thread>
#include <chrono>

int main()
{
	srand(time(NULL));
	
	GameManager &gm = GameManager::GetInstance();
	gm.GameStart();

	return (0);
}
