#pragma once

#include "level3DRender/LevelRender.h"

class Player;
class GameCamera;
class Enemy1;
class Enemy2;
class SoftFloor;
class ConeWall;
class StageNo1Level;
class Shell;

class StageNo1:public IGameObject
{
public:
	StageNo1();
	~StageNo1();
	bool Start();
	void MakeLevel();
	void Update();
	void Death();
	void Render(RenderContext& rc);

private:
	PhysicsStaticObject m_physicsStaticObject;
	ModelRender m_modelRender;
	LevelRender m_levelRender;

	int m_numEnemy1 = 0;

	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;

	std::vector<StageNo1Level*> m_stageNo1Levels;
	std::vector<Enemy1*> m_enemy1s;
	std::vector<Enemy2*> m_enemy2s;
	std::vector<Shell*>	 m_shells;
};

