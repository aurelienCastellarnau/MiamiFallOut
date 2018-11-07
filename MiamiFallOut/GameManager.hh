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

	unsigned int GetRandomInt(int a, int b);
	void MoveLaunch();
	void GameStart();
	Scene* GetScene() const;
	
private:
	bool _init;
	bool _gameStarted = false;

	Scene* _scene;
	ScoreManager* _score_manager;
	TimeManager* _tm;
	sf::Event _event;
	sf::Text _textFPS;
	sf::Font _fontFPS;

	GameManager(const GameManager &);
	GameManager();
	GameManager &operator=(const GameManager &);
	void SetScene(Scene *scene);
	void SetScoreManager(ScoreManager* score_manager);
	void GameLoop();
	void MenuLoop(sf::RenderWindow *);
	const double FPS = 120;
	const double ELAPSED_TIME_FPS = 1000 / FPS;
};