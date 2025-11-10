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
	void GetRoatation(Quaternion& rotation)
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
	bool Start();
	void Update();
	void Collision();
	void DeleteTimer();
	void Rotation();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

private:
	Vector3     m_moveSpeed;
	Vector3     m_position;
	Vector3     m_scale ;
	Vector3     m_collisionPos;
	Quaternion  m_rotation;
	ModelRender m_shellRender;

	bool m_coliisionProduce = false;
	float m_deleteTimer = 0.0f;
	float m_deleteTime = 20.0f;

	Enemy2* m_Enemy2 = nullptr;

};

