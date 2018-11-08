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

int ScoreManager::GetScore() const
{
	return _score;
}

void ScoreManager::SetScore(int score)
{
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
	for (ShapeEntity* const& it : _entities)
	{
		if (it->isPlayer())
		{
 			Player* player = dynamic_cast<Player*>(it);
			std::list<Bullet*>bullets = player->GetBullets();
			sf::Shape* shape1 = it->GetShape();
			sf::FloatRect bounds1 = shape1->getGlobalBounds();
			for (ShapeEntity* const& in_it : _entities)
			{
				sf::Shape* shape2 = in_it->GetShape();
				sf::FloatRect bounds2 = shape2->getGlobalBounds();
				if (!in_it->isPlayer())
				{
					for (ShapeEntity* const& it_bullet : bullets)
					{
						sf::Shape* bullet_shape = it_bullet->GetShape();
						sf::FloatRect bullet_bound = bullet_shape->getGlobalBounds();
						if (bullet_bound.intersects(bounds2))
						{
							_score++;
							_hit++;
							in_it->SetIntersect(true);
						}
					}
				}
				if (it != in_it) {
					if (bounds1.intersects(bounds2)) {
						it->SetIntersect(true);
					}
				}
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
