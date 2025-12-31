#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "FireBall.h"
#include "SoundManager.h"

namespace
{
	const float BODY_COLLISION_RADIUS = 10.0f;
	const float BODY_COLLISION_HEIGHT = 3.0f;
	const Vector3 BODY_COLLISION_SIZE = {250.0f,250.0f,500.0f};

	const float CHARACON_RADIUS = 50.0f;
	const float CHARACON_HEIGHT = 10.0f;

	const float GRAVITY = 200.0f;

	const float ATTACK_COOL_TIME = 2.0f;
	const float ATTACK_RANGE = 1000.0f;
	const float FIRE_SPEED = 1200.0f;

	const float PLAYER_BOUNCE = 1000.0f;
}

Boss::Boss()
{

}

Boss::~Boss()
{
	DeleteGO(m_bodyColl);
	DeleteGO(m_damageSE);
}

bool Boss::Start()
{
	//AnimClips();

	/*m_modelRender.Init("Assets/modelData/boss/boss2.tkm", m_animClips,
		enBossState_Num,enModelUpAxisY);*/

	m_modelRender.Init("Assets/modelData/boss/boss2.tkm");

	m_player = FindGO<Player>("player");

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_charaCon.Init(
		CHARACON_RADIUS,
		CHARACON_HEIGHT,
		m_position
	);

	m_bossState = enBossState_Idle;
	m_forward = Vector3::AxisZ;

	MakeBodyColl();

	return true;
}

void Boss::AnimClips()
{
	m_animClips[enBossState_Idle].Load("Assets/animData/bossAnimData/boss2Attack.tka");
	m_animClips[enBossState_Idle].SetLoopFlag(false);
	m_animClips[enBossState_Chase].Load("Assets/animData/bossAnimData/boss2Attack.tka");
	m_animClips[enBossState_Chase].SetLoopFlag(false);
	m_animClips[enBossState_Attack].Load("Assets/animData/bossAnimData/boss2Attack.tka");
	m_animClips[enBossState_Attack].SetLoopFlag(true);
	m_animClips[enBossState_Dead].Load("Assets/animData/bossAnimData/boss2Attack.tka");
	m_animClips[enBossState_Dead].SetLoopFlag(false);
}

void Boss::MakeBodyColl()
{
	m_bodyColl = NewGO<CollisionObject>(0);
	m_bodyCollPos = m_position;
	m_bodyCollPos += m_up * 100.0f;
	m_bodyCollPos += m_forward* 100.0f;
	m_bodyColl->SetIsEnableAutoDelete(false);
	m_bodyColl->CreateBox(m_bodyCollPos,
		Quaternion::Identity,
		BODY_COLLISION_SIZE
	);
	m_bodyColl->SetName("boss_body_coll");
}

void Boss::Update()
{
	//m_moveSpeed.y -= GRAVITY;
	if (m_hp <= 0)
	{
		m_bossState = enBossState_Dead;
		//return;
	}

	Chase();

	Rotation();

	Collision();

	ManageState();

	m_bodyCollPos = m_charaCon.GetPosition();
	m_bodyCollPos.y += 100.0f;
	m_bodyColl->SetPosition(m_bodyCollPos);
	m_bodyColl->SetRotation(m_rotation);

	if (m_bossState != enBossState_Idle)
	{
		m_modelDrawFlag = true;
	}

	m_modelRender.Update();
}

void Boss::Damage()
{
	m_hp--;
	SoundManager*sound=FindGO<SoundManager>("soundManager");
	m_damageSE = sound->PlayingSound(Sound::enSound_EnDamageSE, false);

}

void Boss::Chase()
{
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	Vector3 modelPos = m_position;
	modelPos.y += 2.5f;
	m_modelRender.SetPosition(modelPos);
	if (m_bossState != enBossState_Chase)
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		return;
	}

	Vector3 diff = m_player->GetPosition() - m_position;
	//diff.y = 0.0f;

	diff.Normalize();

	//移動速度
	m_moveSpeed = diff * 350.0f;
	//m_moveSpeed.y -= GRAVITY;

	//m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}

	/*Vector3 modelPos = m_position;
	modelPos.y += 2.5f;*/
	m_modelRender.SetPosition(modelPos);
}

void Boss::Rotation()
{
	if (m_bossState != enBossState_Dead)
	{
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.y = 0.0f;
		if (diff.LengthSq() < 1e-6f)
		{
			return;
		}

		diff.Normalize();
		const float PI = 3.14159265;
		float angle = atan2(diff.x, diff.z);
		m_rotation.SetRotationY(angle + PI);
		m_modelRender.SetRotation(m_rotation);
	}
}

void Boss::Collision()
{
		/*const auto& shellColl = g_collisionObjectManager->FindCollisionObjects("player_jump_attack");
		for (auto collision : shellColl)
		{
			if (collision->IsHit(m_bodyColl))
			{
				m_hp--;
				m_player->m_moveSpeed.y = PLAYER_BOUNCE;
			}
		}*/
}

void Boss::Appearance()
{
	m_moveSpeed.y -= 10.0f;
	if (m_charaCon.IsOnGround())
	{
		m_bossState = enBossState_Chase;
	}
}

void Boss::FireBallAttack()
{

}

const bool Boss::SearchPlayer() const
{
	return false;
}

void Boss::ProcessCommonStateTransition()
{
	m_attackCoolTime = g_gameTime->GetFrameDeltaTime();
	


}

void Boss::ProcessIdleStateTransition()
{

}

void Boss::ProcessAttackStateTransition()
{
	m_attackCoolTime += g_gameTime->GetFrameDeltaTime();
	if (m_attackCoolTime < ATTACK_COOL_TIME)
	{
		return;
	}

	Vector3 diff = m_player->GetPosition() - m_position;
	float distSq = diff.LengthSq();
	if (distSq > ATTACK_RANGE * ATTACK_RANGE)
	{
		return;
	}

	Vector3 firePos = m_position;
	firePos.y += 150.0f; 
	firePos += GetForwardXZ() * 200.0f; 

	Vector3 dir = m_player->GetPosition() - firePos;
	if (dir.LengthSq() < 1e-6f) dir = GetForwardXZ();

	dir.Normalize();

	
	m_fireBall = NewGO<FireBall>(0, "fireBall");
	if (m_fireBall)
	{
		m_fireBall->SetPosition(firePos);

		// 移動速度は direction * speed
		
		m_fireBall->SetMoveSpeed(dir * FIRE_SPEED);
	}

	m_attackCoolTime = 0.0f; // クールリセット

	// 共通状態遷移（HPチェックなど）
	ProcessCommonStateTransition();
}

void Boss::ProcessDeadStateTransition()
{
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_modelRender.SetScale(m_scale.x, 0.3f, m_scale.z);
	m_charaCon.RemoveRigidBoby();

	DeleteGO(m_bodyColl);

	

	if (m_deleteTimer >= m_deleteTime)
	{
		DeleteGO(this);
	}
}

Vector3 Boss::GetForwardXZ()
{
	Vector3 forward = Vector3::AxisZ;
	Quaternion rot = m_rotation;
	rot.Apply(forward);
	forward.y = 0.0f;
	if (forward.Length() > 1e-5f)
	{
		forward.Normalize();
		return forward;
	}
}

void Boss::ManageState()
{
	switch (m_bossState)
	{
	case enBossState_Idle:
		m_modelDrawFlag = false;
		ProcessIdleStateTransition();
		break;
	case enBossState_App:
		Appearance();
		break;
	case enBossState_Chase:
		
		break;
	case enBossState_Attack:
		ProcessAttackStateTransition();
		m_modelRender.PlayAnimation(enBossState_Attack);
		break;
	case enBossState_Dead:
		ProcessDeadStateTransition();
		break;
	case enBossState_Num:

		break;
	default:
		break;
	}
}

void Boss::Render(RenderContext& rc)
{
	if (m_modelDrawFlag == true)
	{
		m_modelRender.Draw(rc);
	}
}

const bool Boss::IsDead() const
{
	if (m_bossState == enBossState_Dead)
	{
		return true;
	}
	return false;
}