#pragma once
class Item:public IGameObject
{
public:
	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext& rc);

	ModelRender m_shellRender;
	Vector3     m_position;
	Vector3     m_scale;
	Quaternion  m_rotation;
};

class Shell : public Item
{
public:
	bool Start();
	void Collision();
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	Vector3     m_moveSpeed;
};

