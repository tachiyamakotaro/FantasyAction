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
class ItemSpawner;
class SoundManager;

class BossStage:public IGameObject
{
public:
	BossStage();
	~BossStage();
	bool Start() override;
	void Update()override;
	void MakeLevel();
	void MakeColl();
	void BossStateChange();
	void Death();
	void Goal();
	void ClearScene();
	void GameOverScene();
	void DispTime();
	void TimeUp();
	void AppGoal();
	void Render(RenderContext& rc) override;

private:
	PhysicsStaticObject m_staticObj;
	FontRender m_timeRender;
	LevelRender m_levelRender;
	Vector3 m_collPos = Vector3::Zero;

	float m_timer = 120.0f;
	bool m_bossDead = false;

	//BossStageLevel* m_bossStage;
	Player* m_player;
	SkyCube* m_skyCube = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GoalPoint* m_goalPoint = nullptr;
	GameScene* m_gameScene = nullptr;
	StageCount* m_stageCount = nullptr;
	Boss* m_boss = nullptr;
	CollisionObject* m_bossStateChangeColl = nullptr;

	SoundManager* soundManager;
	SoundSource* m_bossStageBGM;
	SoundSource* m_bossBGM;

	std::vector<CastleFloor*> m_castleFloors;
	std::vector<CastleWall*> m_castleWalls;

	std::vector<Enemy1*> m_enemy1s;
	std::vector<Enemy2*> m_enemy2s;
	std::vector<Shell*>	 m_shells;
	std::vector<ItemSpawner*> m_itemSpawners;
};

