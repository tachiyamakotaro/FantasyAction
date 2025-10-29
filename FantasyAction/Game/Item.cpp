#include "stdafx.h"
#include "Item.h"


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

	m_shellRender.Update();
}

void Item::Rotation()
{
	m_rotation.AddRotationDegY(ROTATION_SPEED);
	m_shellRender.SetRotation(m_rotation);
}

void Item::Render(RenderContext& rc)
{
	m_shellRender.Draw(rc);
}

//çbóÖÇÃÉAÉCÉeÉÄ
bool Shell::Start()
{
	m_shellRender.Init("Assets/modelData/koura.tkm");

	return true;
}

void Shell::Collision()
{
	
}