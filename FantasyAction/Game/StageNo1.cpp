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
	Death();

	Goal();
}

void StageNo1::Death()
{
	if (m_player->m_position.y < -500.0f)
	{
		DeleteGO(this);
	}
	if (m_player->m_playerState == m_player->enPlayerState_Death)
	{
		DeleteGO(this);
	}
}

void StageNo1::Goal()
{
	bool a = m_goalPoint->IsGoal();
	if (a == true)
	{
		m_gameScene = NewGO<GameClear>(0, "gameClear");
		DeleteGO(this);
	}
}

void StageNo1::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
	//m_modelRender.Draw(rc);
}
