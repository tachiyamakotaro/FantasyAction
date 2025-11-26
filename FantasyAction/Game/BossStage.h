#pragma once

#include "level3DRender/LevelRender.h"

class Player;
class BossStageLevel;
class GameCamera;

class BossStage:public IGameObject
{
public:
	BossStage();
	~BossStage();
	bool Start() override;
	void Update()override;
	void MakeLevel();
	void Render(RenderContext& rc) override;

private:
	LevelRender m_levelRender;

	BossStageLevel* m_bossStage;
	Player* m_player;
	SkyCube* m_skyCube = nullptr;
	GameCamera* m_gameCamera = nullptr;
};

