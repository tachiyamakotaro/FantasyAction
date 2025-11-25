#pragma once

class Player;

class UI:public IGameObject
{
public:
	UI();
	virtual ~UI();
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

protected:

};



/*
 *Hpクラス 
 */
class Hp:public UI
{


public:
	Hp();
	~Hp();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	void SetHP(int hp)
	{
		if (hp < 0)
		{
			m_currentHp = 0;
		}
		else if (hp > m_maxHp)
		{
			m_currentHp = m_maxHp;
		}
		else
		{
			m_currentHp = hp;
		}
	}

	void SetMaxHP(int maxHp)
	{
		if (maxHp < 1)
		{
			m_maxHp = 1;
		}
		else
		{
			m_maxHp = maxHp;
		}

		if (m_currentHp > m_maxHp)
		{
			m_currentHp = m_maxHp;
		}
	}

	void SetHeartSpacing(float s)
	{
		m_heartSpacing = s;
	}

	void SetCentered(bool c)
	{
		m_centered = c;
	}

private:
	Vector3 m_hpUIPos;
	Quaternion m_hpUIRot;
	Vector3 m_hpUIScale;
	SpriteRender m_oneHPUI;
	SpriteRender m_twoHPUI;
	SpriteRender m_threeHPUI;

	Player* m_player;

	int m_currentHp;
	int m_maxHp;
	float m_heartSpacing; //ハート同士の間隔
	bool m_centered;
};

