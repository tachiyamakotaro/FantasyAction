#include "stdafx.h"
#include "Player.h"

namespace
{
	const float CAPSULE_COLLIDER_RADIUS = 25.0f;
	const float CAPSULE_COLLIDER_HEIGHT = 75.0f;
	const float CHARACTER_MOVESPEED = 250.0f;
	const float CHARACTER_JUMPSPEED = 800.0f;
	//ƒ_ƒbƒVƒ…‚Ì”{—¦
	const float CHARACTER_DASHSPEED_MAGNIFICATION = 2.0f;
	const float GRAVITY = 40.0f;
	const float STICK_INPUT = 0.001f;
}

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Clear].Load("Assets/animData/clear.tka");
	m_animationClips[enAnimationClip_Clear].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Death].Load("Assets/animData/KneelDown.tka");
	m_animationClips[enAnimationClip_Death].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips,
		enAnimationClip_Num, enModelUpAxisY);

	m_characterController.Init(CAPSULE_COLLIDER_RADIUS, CAPSULE_COLLIDER_HEIGHT, m_position);

	return true;
}

void Player::Update()
{
	Move();

	Rotation();

	Animation();

	//Damege();

	m_modelRender.Update();
}

void Player::Move()
{
	m_animationState = enAnimationClip_Idle;
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
			m_animationState = enAnimationClip_Run;
		}
		else 
		{
			m_dashFlag = false;
			m_animationState = enAnimationClip_Walk;
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
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_moveSpeed.y = CHARACTER_JUMPSPEED;
			
		}
	}
	else
	{
		m_moveSpeed.y -= GRAVITY;
		m_animationState = enAnimationClip_Jump;
	}
}

void Player::Damege()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_life--;
	}
	if (m_life <= 0)
	{
		m_animationState = enAnimationClip_Death;
		m_moveFlag = false;
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

void Player::Animation()
{
	switch (m_animationState)
	{
	case enAnimationClip_Idle:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case enAnimationClip_Walk:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case enAnimationClip_Run:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	case enAnimationClip_Jump:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case enAnimationClip_Clear:
		m_modelRender.PlayAnimation(enAnimationClip_Clear);
		break;
	case enAnimationClip_Death:
		m_modelRender.PlayAnimation(enAnimationClip_Death);
		break;
	default:
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}