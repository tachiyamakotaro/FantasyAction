#pragma once
class BossStageLevel:public IGameObject
{
public:
	BossStageLevel();
	~BossStageLevel();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	void SetPosition(const Vector3& position)
	{
		m_position = position;
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
	Vector3					m_position;
	Quaternion				m_rotation;
	Vector3					m_scale;
	ModelRender				m_modelRender;
	PhysicsStaticObject		m_staticObject;
};

