#pragma once

class Shell;
class Player;
class Enemy2;

class ItemSpawner:public IGameObject
{
public:
	ItemSpawner();
	~ItemSpawner();
	bool Start() override;
	void Update() override;
	void SpawnTimer();
	
	void SetPosition(const Vector3& position)
	{
		m_spawnPos = position;
	}

	void TrySpawnShell();

	/*bool SetSpawnedEnemy(const bool spawnedEnemy)
	{
		m_spawnedEnemy = spawnedEnemy;
		return m_spawnedEnemy;
	}*/

	const bool PlItemDistance() const;

private:
	Vector3 m_spawnPos=Vector3::Zero;
	float m_cooldownTimer = 0.0f;
	float m_cooldown = 5.0f;
	bool m_canSpawn = true;
	bool m_spawnedEnemy = false;

	Shell* m_shell = nullptr;
	Player* m_player = nullptr;
	Enemy2* m_enemy2 = nullptr;
};

