#pragma once

class Enemy2;

class Item:public IGameObject
{
public:
	bool Start();
	void Update();	
	void Rotation();

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	void GetRotation(Quaternion& rotation)
	{
		rotation = m_rotation;
	}

	void Render(RenderContext& rc);

private:
	
	Vector3     m_position;
	Vector3     m_scale;
	Quaternion  m_rotation;
};

class Shell : public Item
{
public:
	enum ShellMoveState
	{
		Idle,
		PlayerHas,
		Throwing
	};
public:
	bool Start();
	void Update();
	void Collision();
	void DeleteTimer();
	void ShellState();
	void ShellMove();
	void Rotation();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void SetShellMove(const ShellMoveState shellState)
	{
		m_shellState = shellState;
	}

	const ShellMoveState& GetShellMove() const
	{
		return m_shellState;
	}

private:
	Vector3     m_moveSpeed;
	Vector3     m_position;
	Vector3     m_scale ;
	Vector3     m_collisionPos;
	Quaternion  m_rotation;
	ModelRender m_shellRender;
	ShellMoveState   m_shellState = Idle;
	CollisionObject* m_collisionObj;

	bool m_coliisionProduce = false;
	float m_deleteTimer = 0.0f;
	float m_deleteTime = 20.0f;

	Enemy2* m_Enemy2 = nullptr;

};

