#pragma once
const unsigned int WINDOW_WIDTH(1600);
const unsigned int WINDOW_HEIGHT(800);
#include "Scene.hh"
#include "ScoreManager.hh"
class GameManager
{
public:

	static GameManager &GetInstance();
	~GameManager();

	void GameStart();
	void GameLoop();
	void MoveLaunch();

	Scene* GetScene() const;
	
private:
	bool _init = false;
	GameManager(const GameManager &);
	GameManager();
	GameManager &operator=(const GameManager &);
	Scene* _scene;
	ScoreManager* _score_manager;
	void SetScene(Scene *scene);
	void SetScoreManager(ScoreManager* score_manager);
};