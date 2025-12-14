#include "stdafx.h"
#include "ItemSpawner.h"
#include "Item.h"
#include "Player.h"
#include "Enemy2.h"

ItemSpawner::ItemSpawner()
{
}

ItemSpawner::~ItemSpawner()
{
	DeleteGO(m_shell);
}

bool ItemSpawner::Start()
{
	return true;
}

void ItemSpawner::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		if (m_player == nullptr)
		{
			return;
		}
	}

	SpawnTimer();
	if (PlItemDistance() == true)
	{
			TrySpawnShell();
	}
}

void ItemSpawner::SpawnTimer()
{
	float dt = g_gameTime->GetFrameDeltaTime();
	if (m_cooldownTimer >= 0.0f)
	{
		m_cooldownTimer -= dt;
		if (m_cooldownTimer < 0.0f)
		{
			m_cooldownTimer = 10.0f;
			m_canSpawn = true;
		}
	}
}

void ItemSpawner::TrySpawnShell()
{
	if (m_canSpawn == true)
	{
		/*m_shell = NewGO<Shell>(0, "shell");
		m_shell->SetPosition(m_spawnPos);
		m_canSpawn = false;*/
		m_enemy2 = NewGO<Enemy2>(0,"enemy2");
		m_enemy2->SetPosition(m_spawnPos);
		m_enemy2->SetSpawnerFlag(true);
		m_canSpawn = false;
	}
}

const bool ItemSpawner::PlItemDistance() const
{
	Vector3 plDiff = m_player->GetPosition() - m_spawnPos;
	//Vector3 shellDiff = m_shell->GetPosition() - m_spawnPos;
	if (plDiff.Length() <= 500.0f/* or shellDiff.Length() <= 500.0f*/)
	{
		return true;
	}
	return false;
}
