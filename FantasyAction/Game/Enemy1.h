#pragma once
#include "physics/PhysicsGhostObject.h"

class Player;

class Enemy1 :public IGameObject
{
public:
	//エネミーステート
	enum EnEnemyState
	{
		enEnemyState_Idle,		//待機
		//enEnemyState_Patrol,	//巡回
		enEnemyState_Chase,		//追跡
		//enEnemyState_ReceiveDamage,			//被ダメージ。
		enEnemyState_Dead,		//死亡
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
	/// 座標を設定する。
	/// </summary>
	/// <param name="position">座標。</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得する。
	/// </summary>
	/// <returns>座標。</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 回転を設定する。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 大きさを設定する。
	/// </summary>
	/// <param name="scale">大きさ。</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// 追跡処理。
	/// </summary>
	void Chase();
	/// <summary>
	/// 回転処理。
	/// </summary>
	void Rotation();
	/// <summary>
	/// プレイヤーの攻撃との当たり判定処理。
	/// </summary>
	void Collision();
	/// <summary>
	/// プレイヤーを探索する。
	/// </summary>
	/// <returns>プレイヤーが見つかったらtrue。</returns>
	const bool SearchPlayer() const;
	/// <summary>
	/// 各ステートの遷移処理。
	/// </summary>
	void ManageState();
	/// <summary>
	/// 共通のステート遷移処理。
	/// </summary>
	void ProcessCommonStateTransition();
	/// <summary>
	/// 待機ステートの遷移処理。
	/// </summary>
	void ProcessIdleStateTransition();
	/// <summary>
	/// 死亡ステートの遷移処理。
	/// </summary>
	void ProcessDeadStateTransition();
	
	ModelRender					m_modelRender;								//モデルレンダー。
	Vector3						m_position;									//座標。
	Vector3						m_moveSpeed;								//移動速度。
	Vector3						m_forward = Vector3::AxisZ;					//エネミーの正面ベクトル。
	Quaternion					m_rotation;									//回転。
	Vector3						m_scale = Vector3::One;						//大きさ。
	Vector3						m_up = Vector3::AxisY;
	CharacterController			m_charaCon;									//キャラコン。
	EnEnemyState				m_enemyState = enEnemyState_Idle;			//エネミーステート。

	Player* m_player = nullptr;							//プレイヤー。

	std::vector<CollisionObject*>m_bodyCollisions;

	float						m_chaseTimer = 0.0f;						//追跡タイマー。
	float						m_idleTimer = 0.0f;
	float						m_deleteTimer = 0.0f;
	float						m_deleteTime = 1.5f;
};

