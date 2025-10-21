#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace
{
	const Vector3 IN_GAME_CAMERA_POS(0.0f, 125.0f, -350.0f);
	const float CAMERA_MOVE_SPEED = 1000.0f;
	const float CAMERA_COLLISION = 5.0f;
	const float CAMERA_NEAR = 1.0f;
	const float CAMERA_FAR = 15000.0f;
	const float CAMERA_POINT_ABOVE = 80.0f;
	const float CAMERA_POINT_BEHIND = 50.0f;
	const float CAMERA_DISTANCE = 50.0f;
	const float CAMERA_UP_LIMIT = -0.6;
	const float CAMERA_DOWN_LIMIT = 0.7;
	const float CAMERA_CLOSER_SPEED = 1.0f;
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	CameraSet();
	return true;
}

void GameCamera::CameraSet()
{
	m_toCameraPos.Set(IN_GAME_CAMERA_POS);
	m_player = FindGO<Player>("player");
	//�΂˃J�����̏�����
	m_springCamera.Init(
		*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
		CAMERA_MOVE_SPEED,			//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		CAMERA_COLLISION				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B

	);

	g_camera3D->SetNear(CAMERA_NEAR);
	g_camera3D->SetFar(CAMERA_FAR);
}

void GameCamera::Update()
{
	CameraMove();

	m_springCamera.Update();
}

void GameCamera::CameraMove()
{
	//�J�����̍X�V
		//�����_���v�Z����
	Vector3 target = m_player->GetPosition();
	//target.x= m_player->m_position.x;
	////�v���C���[�̑������炿����Ə�𒍎��_�Ƃ���
	target.y += CAMERA_POINT_ABOVE;
	//target.z += CAMERA_POINT_BEHIND;

	Vector3 toCameraPosOld = m_toCameraPos;

	Vector3 pos = target + m_toCameraPos;

	//m_t += 0.01f;
	////if (m_springCamera.GetCamera()->GetTargetToPositionLength() < CAMERA_DISTANCE)
	////{
	//	Vector3 r;
	//	r.Lerp(m_t, m_toCameraPos, target);
	//	pos = r;
	////}

	//�p�b�h�̓��͂��g���ăJ��������
	float posX = g_pad[0]->GetRStickXF();
	float posY = g_pad[0]->GetRStickYF();
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * posX);
	qRot.Apply(m_toCameraPos);
	//X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * posY);
	qRot.Apply(m_toCameraPos);
	
	//�J�����̉�]�̏�����`�F�b�N����
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < CAMERA_UP_LIMIT) {
		//�J�����������������
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > CAMERA_DOWN_LIMIT) {
		//�J������������������
		m_toCameraPos = toCameraPosOld;
	}
	
	//���_���v�Z����
	//Vector3 pos = target + m_toCameraPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷�邱��
	/*g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);*/
	
	//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);
}