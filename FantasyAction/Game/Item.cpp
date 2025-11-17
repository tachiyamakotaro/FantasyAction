#include "stdafx.h"
#include "Item.h"
#include "Enemy2.h"
#include "Player.h"

namespace
{
	const float ROTATION_SPEED = 10.0f;

	//çbóÖÇÃíËêî
	const float SHELLCON_RADIUS = 10.0f;
	const float SHELLCON_HEIGHT = 10.0f;
	const Vector3 COLLISION_SCALE = Vector3(75.0f, 35.0f, 75.0f);
	const float THROW_SPEED = 1200.0f;
	
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

Shell::Shell()
{

}

Shell::~Shell()
{
	DeleteGO(m_collObj);
}

bool Shell::Start()
{
	m_player = FindGO<Player>("player");
	//m_Enemy2 = FindGO<Enemy2>("enemy2");
	m_shellRender.Init("Assets/modelData/koura.tkm");
	//m_position = m_Enemy2->GetPosition();


	m_position.y += 10.0f;
	m_shellRender.SetPosition(m_position);

	m_shellCon.Init(
		SHELLCON_RADIUS,
		SHELLCON_HEIGHT,
		m_position
	);

	m_moveSpeed = Vector3::Zero;

	m_rotation = Quaternion::Identity;

	Collision();

	return true;
}

void Shell::Update()
{
	/*GetRoatation(m_rotation);*/
	Rotation();
	ShellState();
	DeleteTimer();
	m_shellRender.SetPosition(m_position);
	m_shellRender.SetRotation(m_rotation);
	m_shellRender.Update();
}

void Shell::Collision()
{
	if (m_coliisionProduce == false)
	{
		m_collObj = NewGO<CollisionObject>(0);
		m_collisionPos = m_position;
		m_collisionPos.y += 10.0f;
		m_collObj->CreateBox(m_collisionPos,
			Quaternion::Identity,
			COLLISION_SCALE
		);
		m_collObj->SetName("shell_Collision");
		m_collObj->SetTimeLimit(m_deleteTime);
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
		ItemGet();
		break;
	case PlayerHas:
		PlayerFollow();
		break;
	case Throwing:
		ShellMove();
		break;
	default:
		break;
	}
}

void Shell::ItemGet()
{
	m_haveItem = m_player->GetHaveItem();
	m_collObj->SetIsEnable(false);
	Vector3 diff = m_player->GetPosition() - m_position;
	if (diff.Length() <= 100.0f)
	{
		if (m_haveItem==false)
		{
			if (g_pad[0]->IsPress(enButtonX))
			{
				m_player->SetHaveItem(true);
				m_shellState = PlayerHas;
			}
		}
	}
}

void Shell::PlayerFollow()
{
	m_position = m_player->GetPosition();
	m_position.y += 150.0f;
	m_shellCon.SetPosition(m_position);
	m_position = m_shellCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_collisionPos = m_position;
	m_collObj->SetPosition(m_collisionPos);
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		Vector3 forward = m_player->GetForwardXZ();
		m_moveSpeed = forward * THROW_SPEED;
		m_collObj->SetIsEnable(true);
		m_player->SetHaveItem(false);
		m_shellState = Throwing;
	}
}

void Shell::ShellMove()
{
	m_moveSpeed.y -= 50.0f;
	m_position = m_shellCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	//m_position.y -= 10.0f;
	m_collObj->SetPosition(m_position);
}

void Shell::Rotation()
{
	m_rotation.AddRotationDegY(ROTATION_SPEED);
}

void Shell::Render(RenderContext& rc)
{
	m_shellRender.Draw(rc);
}