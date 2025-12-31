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
#include "ItemSpawner.h"
#include "SoundManager.h"


namespace
{
	const Vector3 TIME_POSITION = { -200.0f,475.0f,0.0f };
	const float TIME_SCALE = 2.0f;

	const Vector3 COLL_POS = { -2000.0f,500.0f,8750.0f };
	const Vector3 COLL_SCALE = { 20000.0f,10000.0f,5000.0f };
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
	DeleteGO(m_skyCube);
	DeleteGO(m_goalPoint);
	if (m_bossStateChangeColl != nullptr)
	{
		DeleteGO(m_bossStateChangeColl);
	}
	if (m_bossStageBGM != nullptr)
	{
		DeleteGO(m_bossStageBGM);
	}
	DeleteGO(m_bossBGM);
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
	auto totalSpawners = FindGOs<ItemSpawner>("itemSpawner");
	for (auto spawners : totalSpawners)
	{
		DeleteGO(spawners);
	}


}

bool BossStage::Start()
{
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_skyCube = NewGO<SkyCube>(0, "skyCube");

	m_stageCount = FindGO<StageCount>("stageCount");
	
	m_skyCube->SetType(enSkyCubeType_NightToon_2);
	m_skyCube->SetScale(2500.0f);
	m_skyCube->SetLuminance(0.5f);

	soundManager = FindGO<SoundManager>("soundManager");
	m_bossStageBGM = soundManager->PlayingSound(Sound::enSound_BossStageBGM);

	MakeLevel();
	MakeColl();
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

			if (objData.EqualObjectName(L"spawner"))
			{
				auto itemSpawner = NewGO<ItemSpawner>(1, "itemSpawner");
				itemSpawner->SetPosition(objData.position);
				m_itemSpawners.push_back(itemSpawner);
				return true;
			}

			if (objData.EqualObjectName(L"GoalPoint"))
			{
				m_goalPoint = NewGO<GoalPoint>(0, "goalPoint");
				m_goalPoint->SetPosition(objData.position);
				m_goalPoint->SetRotation(objData.rotation);
				m_goalPoint->SetScale(objData.scale);
				m_goalPoint->SetAppGoal(false);
				return true;
			}

			return false;
		});
}

void BossStage::MakeColl()
{
	m_bossStateChangeColl = NewGO<CollisionObject>(0);
	m_collPos = COLL_POS;
	m_bossStateChangeColl->SetIsEnableAutoDelete(false);
	m_bossStateChangeColl->CreateBox(
		m_collPos,
		Quaternion::Identity,
		COLL_SCALE
	);
	m_bossStateChangeColl->SetName("boss_state_change");
}

void BossStage::Update()
{
	BossStateChange();

	AppGoal();

	DispTime();

	Death();

	Goal();
}

void BossStage::BossStateChange()
{
	const auto& shellColl = g_collisionObjectManager->FindCollisionObjects("boss_state_change");
	for (auto collision : shellColl)
	{
		if (collision->IsHit(m_player->GetCharacterController()))
		{
			m_boss->SetState(Boss::enBossState_App);
			DeleteGO(m_bossStageBGM);
			m_bossBGM = soundManager->PlayingSound(Sound::enSound_BossBGM);
			
			DeleteGO(m_bossStateChangeColl);
		}
	}
}

void BossStage::Death()
{
	if (m_player->m_position.y < -500.0f)
	{
		GameOverScene();
		m_stageCount->SetStageCount(1);
	}
	if (m_player->GetLife() <= 0)
	{
		GameOverScene();
		m_stageCount->SetStageCount(1);
	}
}

void BossStage::Goal()
{
	bool goal = m_goalPoint->IsGoal();
	if (goal == true)
	{
		ClearScene();
	}
}

void BossStage::AppGoal()
{
	bool goal = m_boss->IsDead();
	if (goal == true)
	{
		m_goalPoint->SetAppGoal(true);
	}
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
