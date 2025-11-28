#include "stdafx.h"
#include "Boss.h"

namespace
{
	const float ATTACK_COLLISION_RADIUS = 50.0f;
	const float ATTACK_COLLISION_HEIGHT = 3.0f;

	const float CHARACON_RADIUS = 50.0f;
	const float CHARACON_HEIGHT = 10.0f;
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
	m_modelRender.Init("Assets/modelData/tkm_file/boss2.tkm");

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_charaCon.Init(
		CHARACON_RADIUS,
		CHARACON_HEIGHT,
		m_position
	);

	MakeBodyColl();

	return true;
}

void Boss::MakeBodyColl()
{
	m_bodyColl = NewGO<CollisionObject>(0);
	m_bodyCollPos = m_position;
	m_bodyCollPos += m_up * 50.0f;
	m_bodyColl->SetIsEnableAutoDelete(true);
	m_bodyColl->CreateCapsule(m_bodyCollPos,
		Quaternion::Identity,
		ATTACK_COLLISION_RADIUS,
		ATTACK_COLLISION_HEIGHT
	);
	m_bodyColl->SetName("bossbody_coll");
}

void Boss::Update()
{
	m_modelRender.Update();
}

void Boss::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}