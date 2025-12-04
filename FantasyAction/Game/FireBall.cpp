#include "stdafx.h"
#include "FireBall.h"
#include"Boss.h"

namespace
{
	//çbóÖÇÃíËêî
	const Vector3 COLLISION_SCALE = Vector3(100.0f, 50.0f, 100.0f);
	const float FIRE_SPEED = 1200.0f;
}

FireBall::FireBall()
{

}

FireBall::~FireBall()
{

}

bool FireBall::Start()
{
	m_FireRender.Init("Assets/modelData/FireBall.tkm");

	m_FireRender.SetPosition(m_position);
	m_FireRender.SetRotation(m_rotation);
	m_FireRender.SetScale(m_scale);

	Collision();
	return true;
}

void FireBall::Collision()
{
		m_collObj = NewGO<CollisionObject>(0);
		m_collisionPos = m_position;
		m_collisionPos.y += 10.0f;
		m_collObj->CreateBox(m_collisionPos,
			Quaternion::Identity,
			COLLISION_SCALE
		);
		m_collObj->SetName("fire_Collision");
		m_collObj->SetIsEnableAutoDelete(false);
}

void FireBall::Update()
{
	Fire();
	DeleteTimer();

	m_FireRender.Update();
}

void FireBall::Fire()
{
	float dt = g_gameTime->GetFrameDeltaTime();

	m_position += m_moveSpeed * dt;

	m_FireRender.SetPosition(m_position);
	m_FireRender.SetRotation(m_rotation);

}

void FireBall::DeleteTimer()
{
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	if (m_deleteTimer >= m_deleteTime)
	{
		DeleteGO(this);

	}
}

void FireBall::Render(RenderContext& rc)
{

}
