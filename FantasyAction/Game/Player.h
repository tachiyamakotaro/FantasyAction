#pragma once

class Shell;
class Hp;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void SetJumpCol();
	void SetUI();
	void Update();
	void Move();
	void Dash();
	void Jump();
	void JumpAttack();
	void Damege();
	void Invincible();
	void ModelBlink();
	void Collision();
	void Rotation();
	void PlayerState();
	void Animation();
	void Render(RenderContext& rc);
	//プレイヤーの前方ベクトルを返す
	Vector3 GetForwardXZ();

	const bool IsMove()const;
	const bool IsOnGround() const;
	const bool IsXButtonPress() const;
	const bool IsShellIdle()const;
	const bool IsShellHas() const;

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

	/*const void GetPlayerState()const
	{
		return m_playerState=enPlayerState_Num;
	}*/

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	//void SetScale(const Vector3& scale)
	//{
	//	m_scale = scale;
	//}

	const int GetLife()const
	{
		return m_life;
	}

	const int GetMaxLife()const
	{
		return m_maxLife;
	}

	void SetHaveItem(const bool& haveItem)
	{
		m_haveItem = haveItem;
	}

	bool GetHaveItem()const
	{
		return m_haveItem;
	}


	CharacterController		m_characterController;
	Quaternion				m_rotation;
	Vector3					m_position;
	Vector3					m_startPosition;
	Vector3					m_down = Vector3::AxisY;
	Vector3					m_moveSpeed;



	enum EnPlayerState {
		enPlayerState_Idle = 0,
		enPlayerState_Walk,
		enPlayerState_Run,
		enPlayerState_Jump,
		enPlayerState_Clear,
		enPlayerState_Death,
		enPlayerState_Num,
	};
	EnPlayerState m_playerState = enPlayerState_Idle;
	AnimationClip m_animationClips[enPlayerState_Num];
private:

	bool m_moveFlag = true;
	bool m_dashFlag = false;
	bool m_damege = false;
	bool m_jumpColFlag = false;
	bool m_haveItem = false;
	bool m_dispModel = true;

	float m_invincibleTimer = 0.0f;
	float m_invincibleLimit = 2.0f;
	float m_tripleJumpTime = 0.2f;
	float m_tripleJumpTimer = 0.0f;
	float m_dispModelTimer = 0.0f;

	int m_jumpState = 0;
	int m_life = 3;
	int m_maxLife = 3;

	SoundSource* m_jumpSe;
	CollisionObject* m_jumpCol = nullptr;
	Shell* m_shell = nullptr;
	Hp* m_hpUI = nullptr;

	Vector3 m_scale;
	Vector3 m_jumpColPos;
	ModelRender m_modelRender;
	FontRender  m_lifeRender;
	//bool m_renderFlag = true;
};

