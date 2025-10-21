#pragma once
class StageNo1Level:public IGameObject
{
public:
	StageNo1Level();
	~StageNo1Level();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;


	ModelRender				m_modelRender;				//モデルレンダラー。
	Vector3					m_position;					//座標。
	Vector3					m_scale;					//大きさ。
	Quaternion				m_rotation;					//回転。
	PhysicsStaticObject		m_physicsStaticObject;		//静的物理オブジェクト。
};

