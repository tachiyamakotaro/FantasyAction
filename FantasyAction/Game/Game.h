#pragma once

#include "Level3DRender/LevelRender.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;
class GameCamera;
class StageNo1;
class GameOver;
class GameScene;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void ReStart();
	void Render(RenderContext& rc);

private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	TknFile m_tknFile;

	Player* m_player;
	GameCamera* m_gameCamera;
	StageNo1* m_stageNo1;
	GameOver* m_gameOver;
	GameScene* m_gameScene;
};

