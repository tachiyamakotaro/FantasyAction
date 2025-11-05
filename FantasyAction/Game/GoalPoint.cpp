#include "stdafx.h"
#include "GoalPoint.h"
#include "Player.h"

namespace
{
	const std::string GOAL_POINT_MODEL_PATH = "Assets/modelData/GoalPoint.tkm";

	const Vector3 GOAL_OBJ_SCALE = Vector3(200.0f, 200.0f, 200.0f);
}

bool GoalPoint::Start()
{
	m_goalPointModel.Init(GOAL_POINT_MODEL_PATH.c_str());

	m_player = FindGO<Player>("player");

	MakeGoalObj();

	return true;
}

void GoalPoint::MakeGoalObj()
{
	m_goalCollisionObject.CreateBox(m_position, m_rotation, Vector3(GOAL_OBJ_SCALE));
}

void GoalPoint::Update()
{
	m_goalPointModel.SetPosition(m_position);
	m_goalPointModel.SetRotation(m_rotation);
	m_goalPointModel.SetScale(m_scale);
	m_goalPointModel.Update();
}

void GoalPoint::Render(RenderContext& rc)
{
	m_goalPointModel.Draw(rc);
}

const bool GoalPoint::IsGoal() const
{
	if (!m_player)
	{
		return false;
	}

	if (m_goalCollisionObject.IsHit(m_player->GetCharacterController()))
	{
		return true;
	}

	return false;
}
