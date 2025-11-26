#include "stdafx.h"
#include "BossStage.h"
#include "Player.h"
#include "BossStageLevel.h"
#include "GameCamera.h"

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

}

bool BossStage::Start()
{
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	//m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetType(enSkyCubeType_SunriseToon);
	m_skyCube->SetScale(2500.0f);
	m_skyCube->SetLuminance(0.5f);

	MakeLevel();
	return true;
}

void BossStage::MakeLevel()
{
	m_levelRender.Init("Assets/level/bossStage.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"bossStage"))
			{
				m_bossStage = NewGO<BossStageLevel>(0);
				m_bossStage->SetPosition(objData.position);
				m_bossStage->SetRotation(objData.rotation);
				m_bossStage->SetScale(objData.scale);

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

}

void BossStage::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}
