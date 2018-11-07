#pragma once
const unsigned int WINDOW_WIDTH(1600);
const unsigned int WINDOW_HEIGHT(800);
#include "Scene.hh"
#include "ScoreManager.hh"
#include "TimeManager.hh"

class TimeManager;
class GameManager
{
public:

	static GameManager &GetInstance();
	~GameManager();

	void GameStart();
	void GameLoop();
	unsigned int GetRandomInt(int a, int b);
	void MoveLaunch();

	Scene* GetScene() const;
	
private:
	bool _init = false;
	GameManager(const GameManager &);
	GameManager();
	GameManager &operator=(const GameManager &);
	Scene* _scene;
	ScoreManager* _score_manager;
	sf::Font _fontFPS;
	sf::Text _textFPS;
	TimeManager* _tm;
	void SetScene(Scene *scene);
	void SetScoreManager(ScoreManager* score_manager);
	const double FPS = 120;
	const double ELAPSED_TIME_FPS = 1000 / FPS;
};