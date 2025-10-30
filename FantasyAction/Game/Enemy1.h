#pragma once
#include "physics/PhysicsGhostObject.h"

class Player;

class Enemy1 :public IGameObject
{
public:
	//�G�l�~�[�X�e�[�g
	enum EnEnemyState
	{
		enEnemyState_Idle,		//�ҋ@
		//enEnemyState_Patrol,	//����
		enEnemyState_Chase,		//�ǐ�
		//enEnemyState_ReceiveDamage,			//��_���[�W�B
		enEnemyState_Dead,		//���S
	};
public:
	Enemy1();
	~Enemy1();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Gravity();
	void MakeAttackCollision();
	/// <summary>
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W�B</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ��]��ݒ肷��B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// �傫����ݒ肷��B
	/// </summary>
	/// <param name="scale">�傫���B</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// �ǐՏ����B
	/// </summary>
	void Chase();
	/// <summary>
	/// ��]�����B
	/// </summary>
	void Rotation();
	/// <summary>
	/// �v���C���[�̍U���Ƃ̓����蔻�菈���B
	/// </summary>
	void Collision();
	/// <summary>
	/// �v���C���[��T������B
	/// </summary>
	/// <returns>�v���C���[������������true�B</returns>
	const bool SearchPlayer() const;
	/// <summary>
	/// �e�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ManageState();
	/// <summary>
	/// ���ʂ̃X�e�[�g�J�ڏ����B
	/// </summary>
	void ProcessCommonStateTransition();
	/// <summary>
	/// �ҋ@�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessIdleStateTransition();
	/// <summary>
	/// ���S�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessDeadStateTransition();
	
	ModelRender					m_modelRender;								//���f�������_�[�B
	Vector3						m_position;									//���W�B
	Vector3						m_moveSpeed;								//�ړ����x�B
	Vector3						m_forward = Vector3::AxisZ;					//�G�l�~�[�̐��ʃx�N�g���B
	Quaternion					m_rotation;									//��]�B
	Vector3						m_scale = Vector3::One;						//�傫���B
	Vector3						m_up = Vector3::AxisY;
	CharacterController			m_charaCon;									//�L�����R���B
	EnEnemyState				m_enemyState = enEnemyState_Idle;			//�G�l�~�[�X�e�[�g�B

	Player* m_player = nullptr;							//�v���C���[�B

	std::vector<CollisionObject*>m_bodyCollisions;

	float						m_chaseTimer = 0.0f;						//�ǐՃ^�C�}�[�B
	float						m_idleTimer = 0.0f;
	float						m_deleteTimer = 0.0f;
	float						m_deleteTime = 1.5f;
};

