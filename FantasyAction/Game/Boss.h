#pragma once

class Player;
class Shell;

class Boss:public IGameObject
{
public:
	//ボスステート
	enum EnBossState
	{
		enBossState_Idle,
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

	//void Move();

	void Chase();
	
	void Rotation();
	
	void Collision();

	const bool SearchPlayer() const;
	
	void ManageState();

	void ProcessCommonStateTransition();
	
	void ProcessIdleStateTransition();

	void ProcessAttackStateTransition();
	
	void ProcessDeadStateTransition();

private:
	ModelRender m_modelRender;
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale;
	Vector3						m_moveSpeed;							
	Vector3						m_forward = Vector3::AxisZ;
	Vector3						m_up = Vector3::AxisY;
	Vector3						m_bodyCollPos;
	CharacterController			m_charaCon;

	EnBossState m_bossState = enBossState_Idle;
	AnimationClip m_animClips[enBossState_Num];

	Player* m_player = nullptr;
	Shell* m_shell = nullptr;
	CollisionObject* m_bodyColl = nullptr;

	float						m_idleTimer = 0.0f;
	float						m_deleteTimer = 0.0f;
	float						m_deleteTime = 1.5f;
	int m_hp = 3;	
};

