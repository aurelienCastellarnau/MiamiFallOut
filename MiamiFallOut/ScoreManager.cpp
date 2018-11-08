#include "stdafx.h"
#include "ScoreManager.hh"
#include "TimeManager.hh"
#include "ShapeEntity.hh"
#include "GameManager.hh"
#include "Player.hh"

ScoreManager::ScoreManager() {}

ScoreManager::ScoreManager(sf::RenderWindow* window)
{
	_score = 0;
	_end_condition = 0;
	_window = window;
}

void ScoreManager::SetWindow(sf::RenderWindow* w)
{
	_window = w;
}

sf::RenderWindow* ScoreManager::GetWindow() const
{
	return _window;
}

std::list<ShapeEntity*> ScoreManager::GetEntities() const
{
	return _entities;
}

Player* ScoreManager::GetPlayer() const
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

int ScoreManager::GetScore() const
{
	return _score;
}

void ScoreManager::SetScore(int score)
{
	GameManager::GetInstance().SetScore(score);
	_score = score;
}

int ScoreManager::GetHit() const 
{
	return _hit;
}

void ScoreManager::SetHit(int hit)
{
	_hit = hit;
}

bool ScoreManager::GetEndCondition() const
{
	return _end_condition;
}

void ScoreManager::SetEndCondition(bool end_condition)
{
	_end_condition = end_condition;
}

void ScoreManager::AddEntity(ShapeEntity* const entity)
{
	_entities.push_back(entity);
}

void ScoreManager::RemoveEntity(ShapeEntity* const entity)
{
	_entities.remove(entity);
}

void ScoreManager::Update()
{
	// on compare les entités pour évaluer la scene
	// on agit une fois, en partant du player
 	Player* player = GetPlayer();
	if (player == NULL)
	{
		return;
	}
	sf::Shape* shape_player = player->GetShape();
	sf::FloatRect bounds_player = shape_player->getGlobalBounds();
	// on itère sur toute les entités du score_manager
	for (ShapeEntity* const& in_it : _entities)
	{
		// si c'est un ennemi
		if (!in_it->isPlayer())
		{
			// on extrait sa forme et ses bordures
			sf::Shape* shape_enemy = in_it->GetShape();
			sf::FloatRect bounds_enemy = shape_enemy->getGlobalBounds();
			// on vérifie si une balle l'a touché
			for (ShapeEntity* it_bullet : player->GetBullets())
			{
				Bullet* bullet = dynamic_cast<Bullet*>(it_bullet);
				sf::Shape* bullet_shape = it_bullet->GetShape();
				sf::FloatRect bullet_bound = bullet_shape->getGlobalBounds();
				if (bullet_bound.intersects(bounds_enemy))
				{
					SetScore(_score += 50);
					_hit++;
					in_it->SetIntersect(true);
					player->RemoveBullet(bullet);
					delete it_bullet;
				}
			}
			if (bounds_player.intersects(bounds_enemy)) {
				player->SetIntersect(true);
			}
		}
	}
}

// IObserver implementation
// Cost a lot...
void ScoreManager::Notify(IObservable *observable)
{
	// observable->OnNotify();
	return;
}

ScoreManager::~ScoreManager()
{
}
