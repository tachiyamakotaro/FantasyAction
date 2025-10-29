#include "stdafx.h"
#include <algorithm>
#include "Enemy2.h"
#include "Player.h"
#include "Item.h"

namespace
{
	const float CHARACON_RADIUS = 50.0f;
	const float CHARACON_HEIGHT = 10.0f;
	const float ATTACK_COLLISION_RADIUS = 50.0f;
	const float ATTACK_COLLISION_HEIGHT = 5.0f;
	const float GRAVITY = 200.0f;
	const float HIGHER = 30.0f;
	const float PLAYER_BOUNCE = 1000.0f;
	//const float PLAYER_JUMPSPEED_LIMIT = 900.0f;
}

bool Enemy2::Start()
{
	m_modelRender.Init("Assets/modelData/nokonoko.tkm");

	m_player = FindGO<Player>("player");

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_charaCon.Init(
		CHARACON_RADIUS,
		CHARACON_HEIGHT,
		m_position
	);

	m_enemyState = enEnemyState_Idle;
	m_forward = Vector3::AxisZ; // �����O�x�N�g��
	return true;
}

void Enemy2::Update()
{
	Gravity();

	Chase();

	Rotation();

	Collision();

	MakeAttackCollision();

	ManageState();

	m_modelRender.Update();
}

void Enemy2::Gravity()
{
	m_moveSpeed.y -= GRAVITY;
}

void Enemy2::Chase()
{
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	Vector3 modelPos = m_position;
	modelPos.y += 2.5f;
	m_modelRender.SetPosition(modelPos);
	if (m_enemyState != enEnemyState_Chase || !m_player)
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		return;
	}

	Vector3 diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;
	if (diff.LengthSq() > 700.0f * 700.0f)// �����O�Ȃ�Idle��
	{
		m_moveSpeed = Vector3::Zero;
		m_enemyState = enEnemyState_Idle;
		return;
	}

	diff.Normalize();
	float cosv = m_forward.Dot(diff);
	if (cosv > 1.0f)
	{
		cosv = 1.0f;
	}
	else if (cosv < -1.0f)
	{
		cosv = -1.0f;
	}
	if (acosf(cosv) > Math::PI / 180.0f * 120.0f) // ���E�O�Ȃ��~
	{
		m_moveSpeed = Vector3::Zero;
		m_enemyState = enEnemyState_Idle;
	}

	m_moveSpeed = diff * 250.0f;
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

void Enemy2::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotationY(-angle);

	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);

	//�v���C���[�̑O�x�N�g�����v�Z����B
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Enemy2::Collision()
{
	if (m_enemyState == enEnemyState_Dead)
	{
		return;
	}

	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_jump_attack");
	for (auto collision : collisions)
	{
		if (collision->IsHit(m_charaCon))
		{
			m_enemyState = enEnemyState_Dead;

			m_player->m_moveSpeed.y = PLAYER_BOUNCE;

		}
	}
}

void Enemy2::MakeAttackCollision()
{
	if (m_enemyState != enEnemyState_Dead) {

		//�R���W�����I�u�W�F�N�g���쐬����
		auto collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		collisionPosition += m_up * 50.0f;
		collisionObject->CreateCapsule(collisionPosition,
			Quaternion::Identity,
			ATTACK_COLLISION_RADIUS,
			ATTACK_COLLISION_HEIGHT
		);
		collisionObject->SetName("enemy_body_collision");
		m_bodyCollisions.push_back(collisionObject);
	}
}

const bool Enemy2::SearchPlayer() const
{
	Vector3 diff = m_player->GetPosition() - m_position;

	if (diff.LengthSq() <= 700.0f * 700.0f)
	{
		//�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
		diff.Normalize();
		//�G�l�~�[�̐��ʂ̃x�N�g���ƁA�G�l�~�[����v���C���[�Ɍ������x�N�g���́B
		//����(cos��)�����߂�B
		float cos = m_forward.Dot(diff);
		//����(cos��)����p�x(��)�����߂�B
		float angle = acosf(cos);
		//�p�x(��)��120����菬������΁B
		if (angle <= (Math::PI / 180.0f) * 120.0f)
		{
			//�v���C���[���������I
			return true;
		}
	}
	return false;
}

void Enemy2::ProcessCommonStateTransition()
{
	//�e�^�C�}�[���������B
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;

	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z����B
	Vector3 diff = m_player->GetPosition() - m_position;

	//�v���C���[����������
	if (SearchPlayer() == true)
	{
		//�x�N�g���𐳋K������B
		diff.Normalize();
		//�ړ����x��ݒ肷��B
		m_moveSpeed = diff * 250.0f;
		//�ǐՃX�e�[�g�֑J�ڂ���B
		m_enemyState = enEnemyState_Chase;
		return;
	}
	//�v���C���[���������Ȃ���΁B
	else
	{
		m_enemyState = enEnemyState_Idle;
		return;
	}
}

void Enemy2::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//�ҋ@���Ԃ�������x�o�߂�����B
	if (m_idleTimer >= 0.9f)
	{
		//���̃X�e�[�g�֑J�ڂ���B
		ProcessCommonStateTransition();
	}

}

void Enemy2::ProcessDeadStateTransition()
{
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_modelRender.SetScale(m_scale.x, 0.3f, m_scale.z);
	m_charaCon.RemoveRigidBoby();

	ProduceShell();

	for (auto bodyCollision : m_bodyCollisions)
	{
		DeleteGO(bodyCollision);
	}
	if (m_deleteTimer >= m_deleteTime)
	{
		DeleteGO(this);
	}
}

void Enemy2::ProduceShell()
{
	if (m_shell == nullptr)
	{
		m_shell = NewGO<Shell>(0, "shell");
		m_shell->SetPosition(m_position);
	}
}

void Enemy2::ManageState()
{
	switch (m_enemyState)
	{
	case enEnemyState_Idle:
		//�ҋ@�X�e�[�g�̑J�ڏ����B
		ProcessIdleStateTransition();
		break;
	case enEnemyState_Chase:

		break;
	case enEnemyState_Dead:
		//���S�X�e�[�g�̑J�ڏ����B
		ProcessDeadStateTransition();
		break;
	}
}

void Enemy2::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}