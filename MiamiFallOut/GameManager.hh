#pragma once
const unsigned int WINDOW_WIDTH(1600);
const unsigned int WINDOW_HEIGHT(800);
#include "Scene.hh"
#include "Player.hh"
#include "Enemy.hh"
#include "ScoreManager.hh"
#include "TimeManager.hh"

class TimeManager;
class GameManager
{
public:

	static GameManager &GetInstance();
	~GameManager();

	unsigned int GetRandomInt(int a, int b);
	Player* GetPlayer() const;
	int GetScore() const;
	void SetScore(int score);
	void MoveLaunch();
	void GameStart();
	Scene* GetScene() const;
	sf::RenderWindow* GetWindow() const;
	void SetWindow(sf::RenderWindow* win);

private:
	bool _init;
	bool _gameStarted = false;

	Scene* _scene;
	ScoreManager* _score_manager;
	sf::RenderWindow* _win;
	sf::Font _font;
	sf::Text _textFPS;
	sf::Text _textScore;
	TimeManager* _tm;
	sf::Event _event;

	void settleText();
	void settleObserverPlayer(Player* p);
	void settleObserverEnemy(Enemy* e);
	void playerIsCatched(Player* p);
	void checkEnemiesHit();
	int enemyPoper(int pop_boundary);
	int makeAFrame(sf::RenderWindow* window_ptr, int pop_boundary);

	GameManager(const GameManager &);
	GameManager();
	GameManager &operator=(const GameManager &);
	void setScene(Scene *scene);
	void setScoreManager(ScoreManager* score_manager);
	void gameLoop();
	void menuLoop(sf::RenderWindow *, bool endGame = false);
	const double FPS = 120;
	const double ELAPSED_TIME_FPS = 1000 / FPS;
	int _score;
};