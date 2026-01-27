#pragma once

class Player;
class Shell;
class FireBall;

class Boss:public IGameObject
{
public:
	//ボスステート
	enum EnBossState
	{
		enBossState_Idle,
		enBossState_App,
		enBossState_Chase,
		enBossState_Attack,
		enBossState_Dead,
		enBossState_Num
	};
public:
	Boss();
	~Boss();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;

	void AnimClips();
	void MakeBodyColl();
	void FireBallAttack();

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	void SetState(EnBossState state)
	{
		m_bossState = state;
	}

	void Damage();

	/*CollisionObject* GetBodyColl() const
	{
		return m_bodyColl;
	}*/

	void Chase();
	
	void Rotation();
	
	void Collision();

	void Appearance();

	const bool SearchPlayer() const;
	
	void ManageState();

	void ProcessCommonStateTransition();
	
	void ProcessIdleStateTransition();

	void ProcessAttackStateTransition();
	
	void ProcessDeadStateTransition();

	void BossHpSituation();

	const bool IsDead() const;

	Vector3 GetForwardXZ();

	CollisionObject* m_bodyColl = nullptr;

private:
	ModelRender m_modelRender;
	Vector3 m_position = {0.0f,0.0f,0.0f};
	Quaternion m_rotation={ 0.0f,0.0f,0.0f,0.0f };
	Vector3 m_scale= { 0.0f,0.0f,0.0f };
	Vector3						m_moveSpeed= { 0.0f,0.0f,0.0f };
	Vector3						m_forward = Vector3::AxisZ;
	Vector3						m_up = Vector3::AxisY;
	Vector3						m_bodyCollPos= { 0.0f,0.0f,0.0f };
	CharacterController			m_charaCon;

	EnBossState m_bossState = enBossState_Idle;
	AnimationClip m_animClips[enBossState_Num];

	Player* m_player = nullptr;
	Shell* m_shell = nullptr;
	FireBall* m_fireBall = nullptr;

	SoundSource* m_damageSE;



	bool m_modelDrawFlag = true;
	float						m_idleTimer = 0.0f;
	float						m_deleteTimer = 0.0f;
	float						m_deleteTime = 1.5f;
	float m_attackCoolTime = 0.0f;
	float m_moveSpeedMag = 350.0f;
	int m_hp = 3;	
};


