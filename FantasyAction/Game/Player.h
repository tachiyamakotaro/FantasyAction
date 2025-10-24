#pragma once
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move();
	void Dash();
	void Jump();
	void JumpAttack();
	void Damege();
	//void LifeZeroDeath();
	void Rotation();
	void PlayerState();
	void Animation();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns>���W�B</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �������W��ݒ�B
	/// </summary>
	/// <param name="startPosition">�������W�B</param>
	void SetStartPosition(const Vector3& startPosition)
	{
		m_startPosition = startPosition;
	}
	/// <summary>
	/// �������W���擾�B
	/// </summary>
	/// <param name="startPosition">�������W�B</param>
	void GetStartPosition(Vector3& startPosition) const
	{
		startPosition = m_startPosition;
	}
	///<summary>
	///	�ړ����x�����Z
	/// </summary>
	/// <param name="addMoveSpeed">���Z����ړ����x</param>
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	///<summary>
	///	�L�����N�^�[�R���g���[���[
	/// </summary>
	/// <returns>�L�����N�^�[�R���g���[���[</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	CharacterController		m_characterController;
	Quaternion				m_rotation;
	Vector3					m_position;
	Vector3					m_startPosition;
	Vector3					m_down = Vector3::AxisY;
	Vector3					m_moveSpeed;

	bool m_moveFlag = true;
	bool m_dashFlag = false;
	int m_life = 3;

private:

	SoundSource* m_jumpSe;

	enum EnPlayerState {
		enPlayerState_Idle,
		enPlayerState_Walk,
		enPlayerState_Run,
		enPlayerState_Jump,
		enPlayerState_Clear,
		enPlayerState_Death,
		enPlayerState_Num,
	};
	EnPlayerState m_playerState = enPlayerState_Idle;
	AnimationClip m_animationClips[enPlayerState_Num];
	ModelRender m_modelRender;
	//bool m_renderFlag = true;
};

