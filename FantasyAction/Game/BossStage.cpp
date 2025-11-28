#include "stdafx.h"
#include "BossStage.h"
#include "Player.h"
#include "BossStageLevel.h"
#include "GameCamera.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Item.h"
#include "GoalPoint.h"
#include "GameScene.h"
#include "StageCount.h"


namespace
{
	const Vector3 TIME_POSITION = { -200.0f,475.0f,0.0f };
	const float TIME_SCALE = 2.0f;
}

BossStage::BossStage()
{

}

BossStage::~BossStage()
{
	//DeleteGO(m_bossStage);
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_boss);
	for (auto wall : m_castleWalls)
	{
		DeleteGO(wall);
	}
	for (auto floor : m_castleFloors)
	{
		DeleteGO(floor);
	}
	const auto& enemy1s = FindGOs<Enemy1>("enemy1");
	for (auto enemy1 : enemy1s)
	{
		DeleteGO(enemy1);
	}
	const auto& enemy2s = FindGOs<Enemy2>("enemy2");
	for (auto enemy2 : enemy2s)
	{
		DeleteGO(enemy2);
	}
	auto totalShells = FindGOs<Shell>("shell");
	for (auto shells : totalShells)
	{
		DeleteGO(shells);
	}

}

bool BossStage::Start()
{
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	//m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetType(enSkyCubeType_NightToon_2);
	m_skyCube->SetScale(2500.0f);
	m_skyCube->SetLuminance(0.5f);

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	MakeLevel();
	return true;
}

void BossStage::MakeLevel()
{
	m_levelRender.Init("Assets/level/bossStage1-2.tkl", [&](LevelObjectData& objData)
		{
			/*if (objData.EqualObjectName(L"bossStage"))
			{
				m_bossStage = NewGO<BossStageLevel>(0);
				m_bossStage->SetPosition(objData.position);
				m_bossStage->SetRotation(objData.rotation);
				m_bossStage->SetScale(objData.scale);

				return true;
			}*/

			if (objData.EqualObjectName(L"jouheki"))
			{
				auto wall = NewGO<CastleWall>(0, "castleWall");
				wall->SetPosition(objData.position);
				wall->SetRotation(objData.rotation);
				wall->SetScale(objData.scale);
				m_castleWalls.push_back(wall);

				return true;
			}

			if (objData.EqualObjectName(L"sironoyuka"))
			{
				auto floor = NewGO<CastleFloor>(0, "castleFloor");
				floor->SetPosition(objData.position);
				floor->SetRotation(objData.rotation);
				floor->SetScale(objData.scale);
				m_castleFloors.push_back(floor);

				return true;
			}

			if (objData.EqualObjectName(L"kuribo-") == true)
			{
				auto enemy1 = NewGO<Enemy1>(2, "enemy1");
				enemy1->SetPosition(objData.position);
				enemy1->SetRotation(objData.rotation);
				m_enemy1s.push_back(enemy1);
				return true;
			}

			if (objData.EqualObjectName(L"nokonoko") == true)
			{
				auto enemy2 = NewGO<Enemy2>(3, "enemy2");
				enemy2->SetPosition(objData.position);
				enemy2->SetRotation(objData.rotation);
				m_enemy2s.push_back(enemy2);
				return true;
			}

			if (objData.EqualObjectName(L"boss2"))
			{
				m_boss = NewGO<Boss>(0, "boss");
				m_boss->SetPosition(objData.position);
				m_boss->SetRotation(objData.rotation);
				m_boss->SetScale(objData.scale);

				return true;
			}

			if (objData.EqualObjectName(L"unityChan"))
			{
				m_player = NewGO<Player>(0, "player");
				m_player->SetPosition(objData.position);
				m_player->SetStartPosition(objData.position);
				m_player->SetRotation(objData.rotation);

				return true;
			}

			return false;
		});
}

void BossStage::Update()
{
	DispTime();

	Death();

	Goal();
}

void BossStage::Death()
{
	if (m_player->m_position.y < -500.0f)
	{
		GameOverScene();
	}
	if (m_player->GetLife() <= 0)
	{
		GameOverScene();
	}
}

void BossStage::Goal()
{
	/*bool goal = m_goalPoint->IsGoal();
	if (goal == true)
	{
		ClearScene();
	}*/
}

void BossStage::ClearScene()
{
	m_stageCount = FindGO<StageCount>("stageCount");
	m_stageCount->SetStageCount(0);
	//ゲームシーンに遷移する。
	m_gameScene = NewGO<GameClear>(0, "gameClear");
	DeleteGO(this);
}

void BossStage::GameOverScene()
{
	//ゲームシーンに遷移する。
	m_gameScene = NewGO<GameOver>(0, "gameOver");
	DeleteGO(this);
}

void BossStage::DispTime()
{
	int sec = (int)m_timer;
	m_timer -= g_gameTime->GetFrameDeltaTime();

	wchar_t text[256];
	swprintf_s(text, 256, L"TIME：%02d", sec);
	m_timeRender.SetText(text);
	m_timeRender.SetPosition(TIME_POSITION);
	m_timeRender.SetScale(TIME_SCALE);
	m_timeRender.SetColor(g_vec4Black);

	TimeUp();
}

void BossStage::TimeUp()
{
	if (m_timer <= 0.0f)
	{
		GameOverScene();
	}
}

void BossStage::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
	m_timeRender.Draw(rc);
}
