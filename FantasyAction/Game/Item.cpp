#include "stdafx.h"
#include "Item.h"
#include "Enemy2.h"

namespace
{
	const float ROTATION_SPEED = 10.0f;
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

	Collision();

	return true;
}

void Shell::Update()
{
	/*GetRoatation(m_rotation);*/
	Rotation();
	m_shellRender.SetRotation(m_rotation);
	m_shellRender.Update();
}

void Shell::Collision()
{
	auto collision = NewGO<CollisionObject>(0);
	Vector3 collisionPos = m_position;
	collisionPos.y += 1.0f;
	collision->CreateSphere(collisionPos,
		Quaternion::Identity,
		100.0f
	);
	collision->SetName("shellCollision");
}

void Shell::Rotation()
{
	m_rotation.AddRotationDegY(ROTATION_SPEED);
}

void Shell::Render(RenderContext& rc)
{
	m_shellRender.Draw(rc);
}