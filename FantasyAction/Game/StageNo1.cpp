#include "stdafx.h"
#include "StageNo1.h"
#include "Player.h"
#include "Enemy1.h"
#include "GameCamera.h"
#include "SoftFloor.h"
#include "ConeWall.h"
#include "StageNo1Level.h"

StageNo1::StageNo1()
{

}

StageNo1::~StageNo1()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);

	for (auto softFloor : m_softFloors)
	{
		DeleteGO(softFloor);
	}

	for (auto coneWall : m_coneWalls)
	{
		DeleteGO(coneWall);
	}

	for (auto stageNo1Level : m_stageNo1Levels)
	{
		DeleteGO(stageNo1Level);
	}
}

bool StageNo1::Start()
{
	//m_player = FindGO<Player>("player");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

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
				m_player = NewGO<Player>(0, "player");
				m_player->SetPosition(objData.position);
				m_player->SetStartPosition(objData.position);
				m_player->m_rotation = objData.rotation;
				return true;
			}

			if (objData.EqualObjectName(L"kuribo-") == true)
			{
				auto enemy1 = NewGO<Enemy1>(0,"enemy1");
				enemy1->SetPosition(objData.position);
				enemy1->SetRotation(objData.rotation);
				m_enemy1s.push_back(enemy1);
				return true;
			}

			return false;
		});
}

void StageNo1::Update()
{
	FallDeath();
}

void StageNo1::FallDeath()
{
	if (m_player->m_position.y < -500.0f)
	{
		DeleteGO(this);
	}
}

void StageNo1::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
	//m_modelRender.Draw(rc);
}
