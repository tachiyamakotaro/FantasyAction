#include "stdafx.h"
#include "Item.h"
#include "Enemy2.h"


namespace
{
	const float ROTATION_SPEED = 10.0f;
	const Vector3 COLLISION_SCALE = Vector3(75.0f, 35.0f, 75.0f);
}

bool Item::Start()
{
	return true;
}

void Item::Update()
{
	
	Rotation();
	
}

void Item::Rotation()
{
	m_rotation.AddRotationDegY(ROTATION_SPEED);
}

void Item::Render(RenderContext& rc)
{

}

//çbóÖÇÃÉAÉCÉeÉÄ
bool Shell::Start()
{
	//m_Enemy2 = FindGO<Enemy2>("enemy2");
	m_shellRender.Init("Assets/modelData/koura.tkm");
	//m_position = m_Enemy2->GetPosition();

	m_position.y += 10.0f;
	m_shellRender.SetPosition(m_position);

	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_moveSpeed=
	m_position += m_moveSpeed * 30.0f;
	m_moveSpeed *= 1000.0f;
	m_rotation.AddRotationDegY(360.0f);

	Collision();

	return true;
}

void Shell::Update()
{
	/*GetRoatation(m_rotation);*/
	Rotation();
	ShellState();
	m_shellRender.SetPosition(m_position);
	m_shellRender.SetRotation(m_rotation);
	m_shellRender.Update();
}

void Shell::Collision()
{
	if (m_coliisionProduce == false)
	{
		m_collisionObj = NewGO<CollisionObject>(0);
		m_collisionPos = m_position;
		m_collisionPos.y += 10.0f;
		m_collisionObj->CreateBox(m_collisionPos,
			Quaternion::Identity,
			COLLISION_SCALE
		);
		m_collisionObj->SetName("shell_Collision");
		m_collisionObj->SetTimeLimit(m_deleteTime);
		m_coliisionProduce = true;
	}
}

void Shell::DeleteTimer()
{
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	if (m_deleteTimer >= m_deleteTime)
	{
		DeleteGO(this);
	}
}

void Shell::ShellState()
{
	switch (m_shellState)
	{
	case Idle:
		break;
	case PlayerHas:
		break;
	case Throwing:
		ShellMove();
		break;
	default:
		break;
	}
}

void Shell::ShellMove()
{
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//m_position.y -= 10.0f;
	m_collisionObj->SetPosition(m_position);
}

void Shell::Rotation()
{
	m_rotation.AddRotationDegY(ROTATION_SPEED);
}

void Shell::Render(RenderContext& rc)
{
	m_shellRender.Draw(rc);
}