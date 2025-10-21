#pragma once
class StageNo1Level:public IGameObject
{
public:
	StageNo1Level();
	~StageNo1Level();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;


	ModelRender				m_modelRender;				//���f�������_���[�B
	Vector3					m_position;					//���W�B
	Vector3					m_scale;					//�傫���B
	Quaternion				m_rotation;					//��]�B
	PhysicsStaticObject		m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�B
};

