#include "stdafx.h"
#include "UI.h"
#include "Player.h"

UI::UI()
{

}

UI::~UI()
{

}

bool UI::Start()
{
	return true;
}

void UI::Update()
{

}

void UI::Render(RenderContext& rc)
{

}



namespace
{
	const Vector3 HP_POS = { 650.0f,450.0f,0.0f };
	const Vector2 HP_RATIO = { 500.0f,500.0f };
	const Vector3 HP_SCALE = { 1.0f,1.0f,0.0f };
}
/**
 * HPÇÃUIÇÃê›íË 
 */

Hp::Hp()
{

}

Hp::~Hp()
{

}

bool Hp::Start()
{
	m_oneHPUI.Init("Assets/sprite/ONEHPUI.DDS", HP_RATIO.x, HP_RATIO.y);
	m_twoHPUI.Init("Assets/sprite/TWOHPUI.DDS", HP_RATIO.x, HP_RATIO.y);
	m_threeHPUI.Init("Assets/sprite/THREEHPUI.DDS", HP_RATIO.x, HP_RATIO.y);

	m_oneHPUI.SetPosition(HP_POS);
	m_oneHPUI.SetScale(HP_SCALE);

	m_twoHPUI.SetPosition(HP_POS);
	m_twoHPUI.SetScale(HP_SCALE);

	m_threeHPUI.SetPosition(HP_POS);
	m_threeHPUI.SetScale(HP_SCALE);

	m_player = FindGO<Player>("player");
	//m_currentHp = m_player->GetLife();
	return true;
}

void Hp::Update()
{
	m_currentHp = m_player->GetLife();

	m_oneHPUI.Update();
	m_twoHPUI.Update();
	m_threeHPUI.Update();
}

void Hp::Render(RenderContext& rc)
{
	switch (m_currentHp)
	{
	case 1:
		m_oneHPUI.Draw(rc);
		break;
	case 2:
		m_twoHPUI.Draw(rc);
		break;
	case 3:
		m_threeHPUI.Draw(rc);
		break;
	default:
		break;
	}
}

