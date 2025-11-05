#pragma once
#include"physics/PhysicsGhostObject.h"

class Player;

class GoalPoint:public IGameObject
{
public:
	bool Start();
	void Update();
	void MakeGoalObj();
	void Render(RenderContext& rc);

	const bool IsGoal() const;

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得。
	/// </summary>
	/// <returns>座標。</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

private:
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale;
	ModelRender m_goalPointModel;
	CollisionObject m_goalCollisionObject;

	Player* m_player = nullptr;
};

