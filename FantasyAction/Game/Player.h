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
	void Damege();
	//void LifeZeroDeath();
	void Rotation();
	void Animation();
	void Render(RenderContext& rc);

	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="position">座標。</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得。
	/// </summary>
	/// <returns>座標。</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 初期座標を設定。
	/// </summary>
	/// <param name="startPosition">初期座標。</param>
	void SetStartPosition(const Vector3& startPosition)
	{
		m_startPosition = startPosition;
	}
	/// <summary>
	/// 初期座標を取得。
	/// </summary>
	/// <param name="startPosition">初期座標。</param>
	void GetStartPosition(Vector3& startPosition) const
	{
		startPosition = m_startPosition;
	}
	///<summary>
	///	移動速度を加算
	/// </summary>
	/// <param name="addMoveSpeed">加算する移動速度</param>
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	///<summary>
	///	キャラクターコントローラー
	/// </summary>
	/// <returns>キャラクターコントローラー</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	Vector3 m_position;
	CharacterController m_characterController;
	Vector3 m_moveSpeed;
	Quaternion m_rotation;
	Vector3 m_startPosition;

	bool m_moveFlag = true;
	bool m_dashFlag = false;
	int m_life = 3;

	SoundSource* m_jumpSe;

	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Clear,
		enAnimationClip_Death,
		enAnimationClip_Num,
	};
	EnAnimationClip m_animationState = enAnimationClip_Idle;
	AnimationClip m_animationClips[enAnimationClip_Num];
	ModelRender m_modelRender;
	//bool m_renderFlag = true;
};

