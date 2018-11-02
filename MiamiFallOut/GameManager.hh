#pragma once
const float WINDOW_WIDTH(1600.0f);
const float WINDOW_HEIGHT(800.0f);
#include "Scene.hh"
class GameManager
{
public:

	static GameManager &GetInstance();
	~GameManager();

	void GameStart();
	void GameLoop();
	
	Scene* GetScene() const;
	
private:
	bool _init = false;
	GameManager(const GameManager &);
	GameManager();
	GameManager &operator=(const GameManager &);

	Scene* _scene;
	void SetScene(Scene *scene);
};