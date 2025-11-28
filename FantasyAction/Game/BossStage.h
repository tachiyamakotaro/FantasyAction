#pragma once

#include "level3DRender/LevelRender.h"

class Player;
//class BossStageLevel;
class GameCamera;
class Enemy1;
class Enemy2;
class Boss;
class Shell;
class GoalPoint;
class GameScene;
class StageCount;
class CastleWall;
class CastleFloor;

class BossStage:public IGameObject
{
public:
	BossStage();
	~BossStage();
	bool Start() override;
	void Update()override;
	void MakeLevel();
	void Death();
	void Goal();
	void ClearScene();
	void GameOverScene();
	void DispTime();
	void TimeUp();
	void Render(RenderContext& rc) override;

private:
	PhysicsStaticObject m_staticObj;
	FontRender m_timeRender;
	LevelRender m_levelRender;

	float m_timer = 120.0f;

	//BossStageLevel* m_bossStage;
	Player* m_player;
	SkyCube* m_skyCube = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GoalPoint* m_goalPoint = nullptr;
	GameScene* m_gameScene = nullptr;
	StageCount* m_stageCount = nullptr;
	Boss* m_boss = nullptr;

	std::vector<CastleFloor*> m_castleFloors;
	std::vector<CastleWall*> m_castleWalls;

	std::vector<Enemy1*> m_enemy1s;
	std::vector<Enemy2*> m_enemy2s;
	std::vector<Shell*>	 m_shells;
};

