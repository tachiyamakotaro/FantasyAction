#include "stdafx.h"
#include "Player.h"

namespace
{
	const float CAPSULE_COLLIDER_RADIUS = 25.0f;
	const float CAPSULE_COLLIDER_HEIGHT = 75.0f;
	const float CHARACTER_MOVESPEED = 250.0f;
	const float CHARACTER_FIRST_JUMPSPEED = 800.0f;
	const float CHARACTER_SECOND_JUMPSPEED = 1000.0f;
	const float CHARACTER_THIRD_JUMPSPEED = 1200.0f;
	const float JUMPSPEED_LIMIT = 1200.0f;
	//ダッシュの倍率
	const float CHARACTER_DASHSPEED_MAGNIFICATION = 2.0f;
	const float GRAVITY = 40.0f;
	const float STICK_INPUT = 0.001f;
	//ジャンプの攻撃判定
	const float JUMP_ATTACK_RADIUS = 10.0f;
	const float JUMP_ATTACK_HEIGHT = 10.0f;
	const Vector3 JUMP_ATTACK_SIZE = { 50.0f,30.0f,50.0f };

	const float   LIFE_TEXT_SCALE = 1.5f;
	const Vector3 LIFE_TEXT_POSITION = { 600.0f,400.0f,0.0f };
	const Vector4 LIFE_COLOR_BLUE = { 0.0f,0.0f,1.0f,1.0f };
	const Vector4 LIFE_COLOR_RED = { 1.0f,0.0f,0.0f,1.0f };
}

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	m_animationClips[enPlayerState_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enPlayerState_Idle].SetLoopFlag(true);
	m_animationClips[enPlayerState_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enPlayerState_Walk].SetLoopFlag(true);
	m_animationClips[enPlayerState_Run].Load("Assets/animData/run.tka");
	m_animationClips[enPlayerState_Run].SetLoopFlag(true);
	m_animationClips[enPlayerState_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enPlayerState_Jump].SetLoopFlag(false);
	m_animationClips[enPlayerState_Clear].Load("Assets/animData/clear.tka");
	m_animationClips[enPlayerState_Clear].SetLoopFlag(false);
	m_animationClips[enPlayerState_Death].Load("Assets/animData/KneelDown.tka");
	m_animationClips[enPlayerState_Death].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips,
		enPlayerState_Num, enModelUpAxisY);

	m_characterController.Init(CAPSULE_COLLIDER_RADIUS, CAPSULE_COLLIDER_HEIGHT, m_position);

	return true;
}

void Player::Update()
{
	Move();

	Rotation();

	Collision();

	Invincible();

	DispStatus();

	PlayerState();

	Animation();

	m_modelRender.Update();
}

void Player::Move()
{
	m_playerState = enPlayerState_Idle;
	if (m_moveFlag == true) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		Vector3 stickL;
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();

		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();

		forward.y = 0.0f;
		forward.Normalize();
		right.y = 0.0f;
		right.Normalize();

		/*forward.y = 0.0f;
		right.y = 0.0f;*/

		right *= stickL.x * CHARACTER_MOVESPEED;
		forward *= stickL.y * CHARACTER_MOVESPEED;

		m_moveSpeed += right + forward;

		if (fabsf(m_moveSpeed.x) >= STICK_INPUT || fabsf(m_moveSpeed.z) >= STICK_INPUT)
		{
			Dash();
		}

		Jump();

		m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	}

	m_modelRender.SetPosition(m_position);
}

void Player::Dash()
{
	if (m_characterController.IsOnGround())
	{
		
		if (g_pad[0]->IsPress(enButtonX)) {
			m_moveSpeed.x *= CHARACTER_DASHSPEED_MAGNIFICATION;
			m_moveSpeed.z *= CHARACTER_DASHSPEED_MAGNIFICATION;
			m_dashFlag = true;
			m_playerState = enPlayerState_Run;
		}
		else 
		{
			m_dashFlag = false;
			m_playerState = enPlayerState_Walk;
		}
	}
	else if (m_dashFlag == true)
	{
		m_moveSpeed.x *= CHARACTER_DASHSPEED_MAGNIFICATION;
		m_moveSpeed.z *= CHARACTER_DASHSPEED_MAGNIFICATION;
	}
}

void Player::Jump()
{
	if (m_characterController.IsOnGround()) 
	{
		m_moveSpeed.y = 0.0f;
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_moveSpeed.y = CHARACTER_FIRST_JUMPSPEED;
			
		}
	}
	else
	{
		m_moveSpeed.y -= GRAVITY;
		m_playerState = enPlayerState_Jump;
	}
	if (m_moveSpeed.y >= JUMPSPEED_LIMIT)
	{
		/*m_moveSpeed.y += JUMPSPEED_LIMIT;
		m_moveSpeed.y = JUMPSPEED_LIMIT;*/
	}
}

void Player::JumpAttack()
{
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	collisionPosition -= m_down ;
	collisionObject->CreateBox(collisionPosition,
		Quaternion::Identity,
		JUMP_ATTACK_SIZE
	);
	collisionObject->SetName("player_jump_attack");
}

void Player::Damege()
{
	if (m_damege == false)
	{
		m_life--;
		m_damege = true;
	}
	if (m_life <= 0)
	{
		m_playerState = enPlayerState_Death;
	}
}

void Player::Invincible()
{
	if (m_damege == true)
	{
		m_invincibleTimer += g_gameTime->GetFrameDeltaTime();
		if (m_invincibleTimer >= m_invincibleLimit)
		{
			m_invincibleTimer = 0.0f;
			m_damege = false;
		}
	}
}

void Player::Collision()
{
	if (m_playerState == enPlayerState_Death)
	{
		return;
	}

	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy_body_collision");
	for (auto collision : collisions)
	{
		if (collision->IsHit(m_characterController))
		{
			Damege();
		}
	}
}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= STICK_INPUT || fabsf(m_moveSpeed.z) >= STICK_INPUT)
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::DispStatus()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"残りHP：%d", m_life);
	m_lifeRender.SetText(wcsbuf);
	m_lifeRender.SetPosition(LIFE_TEXT_POSITION);
	m_lifeRender.SetScale(LIFE_TEXT_SCALE);
	if (m_life == 3) {
		m_lifeRender.SetColor(LIFE_COLOR_BLUE);
	}
	if (m_life == 2) {
		m_lifeRender.SetColor(g_vec4Yellow);
	}
	if (m_life == 1)
	{
		m_lifeRender.SetColor(LIFE_COLOR_RED);
	}
}

void Player::PlayerState()
{
	switch (m_playerState)
	{
	case enPlayerState_Idle:
		
		break;
	case enPlayerState_Walk:
		
		break;
	case enPlayerState_Run:
		
		break;
	case enPlayerState_Jump:
		JumpAttack();

		break;
	case enPlayerState_Clear:
		
		break;
	case enPlayerState_Death:
		
		break;
	default:
		break;
	}
}

void Player::Animation()
{
	switch (m_playerState)
	{
	case enPlayerState_Idle:
		m_modelRender.PlayAnimation(enPlayerState_Idle);
		break;
	case enPlayerState_Walk:
		m_modelRender.PlayAnimation(enPlayerState_Walk);
		break;
	case enPlayerState_Run:
		m_modelRender.PlayAnimation(enPlayerState_Run);
		break;
	case enPlayerState_Jump:
		m_modelRender.PlayAnimation(enPlayerState_Jump);

		break;
	case enPlayerState_Clear:
		m_modelRender.PlayAnimation(enPlayerState_Clear);
		break;
	case enPlayerState_Death:
		m_modelRender.PlayAnimation(enPlayerState_Death);
		break;
	default:
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

	m_lifeRender.Draw(rc);
}