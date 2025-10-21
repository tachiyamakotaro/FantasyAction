#include "stdafx.h"
#include "Enemy1.h"
#include "Player.h"

namespace
{
	const float CHARACON_RADIUS = 20.0f;
	const float CHARACON_HEIGHT = 100.0f;

}

Enemy1::Enemy1()
{

}

Enemy1::~Enemy1()
{

}

bool Enemy1::Start()
{
	m_modelRender.Init("Assets/modelData/kuribo-.tkm");
	//m_modelRender.Init("Assets/modelData/unityChan.tkm");

	m_player = FindGO<Player>("player");

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_charaCon.Init(
		CHARACON_RADIUS,
		CHARACON_HEIGHT,
		m_position
	);
	// ������ԁE���������E�v���C���[�Q�Ƃ̊m�ہi�G���W�����̒T�����ɍ��킹�Ă��������j
	m_enemyState = enEnemyState_Idle;
	m_forward = Vector3::AxisZ; // �����O�x�N�g��
	return true;
}

void Enemy1::Update()
{
	ManageState();

	Chase();

	Rotation();

	m_modelRender.Update();
}

void Enemy1::Chase()
{
	//�ǐՃX�e�[�g�łȂ��Ȃ�A�ǐՏ����͂��Ȃ��B
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}

	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//������Ƃ������f���̍��W��������B
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy1::Rotation()
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

void Enemy1::Collision()
{

}

const bool Enemy1::SearchPlayer() const
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

void Enemy1::ProcessCommonStateTransition()
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
void Enemy1::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//�ҋ@���Ԃ�������x�o�߂�����B
	if (m_idleTimer >= 0.9f)
	{
		//���̃X�e�[�g�֑J�ڂ���B
		ProcessCommonStateTransition();
	}

}

void Enemy1::ProcessWalkStateTransition()
{
	//���̃X�e�[�g�ɑJ�ڂ���B
	ProcessCommonStateTransition();
}

void Enemy1::ProcessRunStateTransition()
{
	//���̃X�e�[�g�ɑJ�ڂ���B
	ProcessCommonStateTransition();
}

void Enemy1::ManageState()
{
	switch (m_enemyState)
	{
	case enEnemyState_Idle:
		//�ҋ@�X�e�[�g�̑J�ڏ����B
		ProcessIdleStateTransition();
		break;
	case enEnemyState_Chase:
		//�ǐՃX�e�[�g�̑J�ڏ����B
		//ProcessChaseStateTransition();
		break;
	case enEnemyState_Dead:
		//���S�X�e�[�g�̑J�ڏ����B
		//ProcessDeadStateTransition();
		break;
	}
}

void Enemy1::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}