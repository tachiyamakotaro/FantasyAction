#include "stdafx.h"
#include "Boss.h"
#include "Player.h"

namespace
{
	const float BODY_COLLISION_RADIUS = 50.0f;
	const float BODY_COLLISION_HEIGHT = 3.0f;
	const Vector3 BODY_COLLISION_SIZE = {250.0f,250.0f,800.0f};

	const float CHARACON_RADIUS = 50.0f;
	const float CHARACON_HEIGHT = 10.0f;

	const float GRAVITY = 200.0f;
}

Boss::Boss()
{

}

Boss::~Boss()
{
	DeleteGO(m_bodyColl);
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

	m_bossState = enBossState_Chase;
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
	m_bodyCollPos += m_forward* 200.0f;
	m_bodyColl->SetIsEnableAutoDelete(false);
	m_bodyColl->CreateBox(m_bodyCollPos,
		Quaternion::Identity,
		BODY_COLLISION_SIZE
	);
	m_bodyColl->SetName("bossbody_coll");
}

void Boss::Update()
{
	m_moveSpeed.y -= GRAVITY;

	Chase();

	Rotation();

	Collision();

	ManageState();

	//m_bossState = enBossState_Attack;

	m_modelRender.Update();
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
	diff.y = 0.0f;

	diff.Normalize();

	//移動速度
	m_moveSpeed = diff * 430.0f;
	m_moveSpeed.y -= GRAVITY;

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
	//if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	//{
	//	//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
	//	//このフレームではキャラは移動していないので旋回する必要はない。
	//	return;
	//}
	////atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	////m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	////atan2を使用して、角度を求めている。
	////これが回転角度になる。
	//float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	////atanが返してくる角度はラジアン単位なので
	////SetRotationDegではなくSetRotationを使用する。
	//m_rotation.SetRotationY(angle);

	////回転を設定する。
	//m_modelRender.SetRotation(m_rotation);

	////プレイヤーの前ベクトルを計算する。
	//m_forward = Vector3::AxisZ;
	//m_rotation.Apply(m_forward);

	Vector3 diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;
	if (diff.LengthSq() < 1e-6f)
	{
		return;
	}

	diff.Normalize();
	const float PI = 3.14159265;
	float angle = atan2(diff.x, diff.z);
	m_rotation.SetRotationY(angle+PI);
	m_modelRender.SetRotation(m_rotation);
}

void Boss::Collision()
{
	const auto& shellColl = g_collisionObjectManager->FindCollisionObjects("shell_Collision");
	for (auto collision : shellColl)
	{
		if (collision->IsHit(m_charaCon))
		{
			m_hp--;
		}
	}
}

const bool Boss::SearchPlayer() const
{
	return false;
}

void Boss::ProcessCommonStateTransition()
{

}

void Boss::ProcessIdleStateTransition()
{

}

void Boss::ProcessAttackStateTransition()
{

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

void Boss::ManageState()
{
	switch (m_bossState)
	{
	case enBossState_Idle:
		ProcessIdleStateTransition();
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
	m_modelRender.Draw(rc);
}