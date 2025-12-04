#pragma once

class Boss;

class FireBall:public IGameObject
{
public:
	FireBall();
	~FireBall();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void Fire();
	void Collision();
	void DeleteTimer();

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	void SetMoveSpeed(const Vector3& moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
private:

	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_scale;
	Vector3 m_collisionPos;
	Quaternion m_rotation;
	ModelRender m_FireRender;

	float m_deleteTimer = 0.0f;
	float m_deleteTime = 20.0f;

	Boss* m_boss = nullptr;
	CollisionObject* m_collObj;
};

