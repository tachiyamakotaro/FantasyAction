#include "stdafx.h"
#include "Item.h"
#include "Enemy2.h"
#include "Player.h"
#include "Boss.h"
#include "ItemSpawner.h"

namespace
{
	const float ROTATION_SPEED = 10.0f;

	//çbóÖÇÃíËêî
	const float SHELLCON_RADIUS = 10.0f;
	const float SHELLCON_HEIGHT = 10.0f;
	const Vector3 COLLISION_SCALE = Vector3(100.0f, 50.0f, 100.0f);
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
	if (m_collObj != nullptr)
	{
		DeleteGO(m_collObj);
	}

}

bool Shell::Start()
{
	m_player = FindGO<Player>("player");
	//m_Enemy2 = FindGO<Enemy2>("enemy2");
	m_boss = FindGO<Boss>("boss");

	//m_spawner = FindGO<ItemSpawner>("ItemSpawner");

	m_shellRender.Init("Assets/modelData/rock.tkm");
	//m_position = m_Enemy2->GetPosition();


	m_position.y += 10.0f;
	m_shellRender.SetPosition(m_position);

	m_moveSpeed = Vector3::Zero;

	m_rotation = Quaternion::Identity;

	CharaCon();
	Collision();

	return true;
}

void Shell::Update()
{
	if (m_deleteFlag == true)
	{
		return;
	}
	/*GetRoatation(m_rotation);*/
	DeleteItem();
	Rotation();
	ShellState();
	m_position = m_shellCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	//m_position.y -= 10.0f;
	m_collObj->SetPosition(m_position);
	
	m_shellRender.SetPosition(m_position);
	m_shellRender.SetRotation(m_rotation);
	m_shellRender.Update();
}

void Shell::CharaCon()
{
	if (m_charaConProduce == false)
	{
		m_shellCon.Init(
			SHELLCON_RADIUS,
			SHELLCON_HEIGHT,
			m_position
		);
		m_charaConProduce = true;
	}

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
		m_collObj->SetIsEnableAutoDelete(false);
		m_collObj->SetIsEnable(false);
		m_coliisionProduce = true;
	}
}

void Shell::DeleteTimer()
{
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	if (m_deleteTimer >= m_deleteTime)
	{
		m_deleteFlag = true;
		return;
	}
}

void Shell::DeleteItem()
{
	const auto& shellColl = g_collisionObjectManager->FindCollisionObjects("boss_body_coll");
	for (auto collision : shellColl)
	{
		if (collision->IsHit(m_collObj))
		{
			m_boss->Damage();
			m_deleteFlag = true;
		}
	}

	if (m_deleteFlag == true)
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
	DeleteTimer();
	m_haveItem = m_player->GetHaveItem();
	Vector3 diff = m_player->GetPosition() - m_position;
	m_collObj->SetIsEnable(false);
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
	m_collObj->SetIsEnable(false);
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		Vector3 forward = m_player->GetForwardXZ();
		m_moveSpeed = forward * THROW_SPEED;
		
		m_player->SetHaveItem(false);
		m_deleteTimer = 10.0f;
		m_shellState = Throwing;
	}
}

void Shell::ShellMove()
{
	DeleteTimer();
	//CharaCon();
	//Collision();
	m_collObj->SetIsEnable(true);
	
	m_moveSpeed.y -= 50.0f;


}

void Shell::Rotation()
{
	m_rotation.AddRotationDegY(ROTATION_SPEED);
}

void Shell::Render(RenderContext& rc)
{
	m_shellRender.Draw(rc);
}