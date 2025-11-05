#include "stdafx.h"
#include "StageNo1.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "GameCamera.h"
#include "StageNo1Level.h"
#include "Item.h"
#include "GoalPoint.h"
#include "GameScene.h"

namespace
{
	const Vector3 TIME_POSITION = { 100.0f,100.0f,100.0f };
	const float TIME_SCALE = 2.0f;
}

StageNo1::StageNo1()
{

}

StageNo1::~StageNo1()
{
	DeleteGO(m_goalPoint);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);

	for (auto stageNo1Level : m_stageNo1Levels)
	{
		DeleteGO(stageNo1Level);
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

bool StageNo1::Start()
{
	//m_player = FindGO<Player>("player");

	m_gameScene = FindGO<GameClear>("gameClear");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	MakeLevel();

	return true;
}

void StageNo1::MakeLevel()
{
	m_levelRender.Init("Assets/level/StageNo1.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"stageNo1") == true)
			{
				auto stageNo1Level = NewGO<StageNo1Level>(0);
				stageNo1Level->m_position = objData.position;
				stageNo1Level->m_rotation = objData.rotation;
				stageNo1Level->m_scale = objData.scale;
				m_stageNo1Levels.push_back(stageNo1Level);
				return true;
			}

			if (objData.EqualObjectName(L"unityChan") == true)
			{
				m_player = NewGO<Player>(1, "player");
				m_player->SetPosition(objData.position);
				m_player->SetStartPosition(objData.position);
				m_player->m_rotation = objData.rotation;
				return true;
			}

			if (objData.EqualObjectName(L"kuribo-") == true)
			{
				auto enemy1 = NewGO<Enemy1>(2,"enemy1");
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

			if (objData.EqualObjectName(L"GoalPoint") == true)
			{
				m_goalPoint = NewGO<GoalPoint>(4, "goalPoint");
				m_goalPoint->SetPosition(objData.position);
				m_goalPoint->SetRotation(objData.rotation);
				m_goalPoint->SetScale(objData.scale);
				return true;
			}

			return false;
		});
}

void StageNo1::Update()
{
	DispTime();

	Death();

	Goal();
}

void StageNo1::Death()
{
	if (m_player->m_position.y < -500.0f)
	{
		GameOverScene();
	}
	if (m_player->GetLife()<=0)
	{
		GameOverScene();
	}
}

void StageNo1::Goal()
{
	bool a = m_goalPoint->IsGoal();
	if (a == true)
	{
		ClearScene();
	}
}

void StageNo1::ClearScene()
{
	//ゲームシーンに遷移する。
	m_gameScene = NewGO<GameClear>(0, "gameClear");
	DeleteGO(this);
}

void StageNo1::GameOverScene()
{
	//ゲームシーンに遷移する。
	m_gameScene = NewGO<GameOver>(0, "gameOver");
	DeleteGO(this);
}

void StageNo1::DispTime()
{
	int sec = (int)m_timer;
	m_timer -= g_gameTime->GetFrameDeltaTime();

	wchar_t text[256];
	swprintf_s(text, 256, L"残り時間：%02d", sec);
	m_timeRender.SetText(text);
	m_timeRender.SetPosition(TIME_POSITION);
	m_timeRender.SetScale(TIME_SCALE);
	m_timeRender.SetColor(g_vec4Black);

	TimeUp();
}

void StageNo1::TimeUp()
{
	if (m_timer <= 0.0f)
	{
		GameOverScene();
	}
}

void StageNo1::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
	m_timeRender.Draw(rc);
	//m_modelRender.Draw(rc);
}
