#include "stdafx.h"
#include <algorithm>
#include "Enemy2.h"
#include "Player.h"
#include "Item.h"

namespace
{
	const float CHARACON_RADIUS = 50.0f;
	const float CHARACON_HEIGHT = 10.0f;
	const float ATTACK_COLLISION_RADIUS = 50.0f;
	const float ATTACK_COLLISION_HEIGHT = 5.0f;
	const float GRAVITY = 200.0f;
	const float HIGHER = 30.0f;
	const float PLAYER_BOUNCE = 1000.0f;
	//const float PLAYER_JUMPSPEED_LIMIT = 900.0f;
}

bool Enemy2::Start()
{
	m_modelRender.Init("Assets/modelData/nokonoko.tkm");

	m_player = FindGO<Player>("player");

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_charaCon.Init(
		CHARACON_RADIUS,
		CHARACON_HEIGHT,
		m_position
	);

	m_enemyState = enEnemyState_Idle;
	m_forward = Vector3::AxisZ; // 初期前ベクトル
	return true;
}

void Enemy2::Update()
{
	Gravity();

	Chase();

	Rotation();

	Collision();

	MakeAttackCollision();

	ManageState();

	m_modelRender.Update();
}

void Enemy2::Gravity()
{
	m_moveSpeed.y -= GRAVITY;
}

void Enemy2::Chase()
{
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	Vector3 modelPos = m_position;
	modelPos.y += 2.5f;
	m_modelRender.SetPosition(modelPos);
	if (m_enemyState != enEnemyState_Chase || !m_player)
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		return;
	}

	Vector3 diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;
	if (diff.LengthSq() > 700.0f * 700.0f)// 距離外ならIdleへ
	{
		m_moveSpeed = Vector3::Zero;
		m_enemyState = enEnemyState_Idle;
		return;
	}

	diff.Normalize();
	float cosv = m_forward.Dot(diff);
	if (cosv > 1.0f)
	{
		cosv = 1.0f;
	}
	else if (cosv < -1.0f)
	{
		cosv = -1.0f;
	}
	if (acosf(cosv) > Math::PI / 180.0f * 120.0f) // 視界外なら停止
	{
		m_moveSpeed = Vector3::Zero;
		m_enemyState = enEnemyState_Idle;
	}

	m_moveSpeed = diff * 250.0f;
	m_moveSpeed.y -= GRAVITY;

	//m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}

	/*Vector3 modelPos = m_position;
	modelPos.y += 2.5f;*/
	m_modelRender.SetPosition(modelPos);
}

void Enemy2::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//プレイヤーの前ベクトルを計算する。
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Enemy2::Collision()
{
	if (m_enemyState == enEnemyState_Dead)
	{
		return;
	}

	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_jump_attack");
	for (auto collision : collisions)
	{
		if (collision->IsHit(m_charaCon))
		{
			m_enemyState = enEnemyState_Dead;

			m_player->m_moveSpeed.y = PLAYER_BOUNCE;

		}
	}
}

void Enemy2::MakeAttackCollision()
{
	if (m_enemyState != enEnemyState_Dead) {

		//コリジョンオブジェクトを作成する
		auto collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		collisionPosition += m_up * 50.0f;
		collisionObject->CreateCapsule(collisionPosition,
			Quaternion::Identity,
			ATTACK_COLLISION_RADIUS,
			ATTACK_COLLISION_HEIGHT
		);
		collisionObject->SetName("enemy_body_collision");
		m_bodyCollisions.push_back(collisionObject);
	}
}

const bool Enemy2::SearchPlayer() const
{
	Vector3 diff = m_player->GetPosition() - m_position;

	if (diff.LengthSq() <= 700.0f * 700.0f)
	{
		//エネミーからプレイヤーに向かうベクトルを正規化する。
		diff.Normalize();
		//エネミーの正面のベクトルと、エネミーからプレイヤーに向かうベクトルの。
		//内積(cosθ)を求める。
		float cos = m_forward.Dot(diff);
		//内積(cosθ)から角度(θ)を求める。
		float angle = acosf(cos);
		//角度(θ)が120°より小さければ。
		if (angle <= (Math::PI / 180.0f) * 120.0f)
		{
			//プレイヤーを見つけた！
			return true;
		}
	}
	return false;
}

void Enemy2::ProcessCommonStateTransition()
{
	//各タイマーを初期化。
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;

	//エネミーからプレイヤーに向かうベクトルを計算する。
	Vector3 diff = m_player->GetPosition() - m_position;

	//プレイヤーを見つけたら
	if (SearchPlayer() == true)
	{
		//ベクトルを正規化する。
		diff.Normalize();
		//移動速度を設定する。
		m_moveSpeed = diff * 250.0f;
		//追跡ステートへ遷移する。
		m_enemyState = enEnemyState_Chase;
		return;
	}
	//プレイヤーを見つけられなければ。
	else
	{
		m_enemyState = enEnemyState_Idle;
		return;
	}
}

void Enemy2::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら。
	if (m_idleTimer >= 0.9f)
	{
		//他のステートへ遷移する。
		ProcessCommonStateTransition();
	}

}

void Enemy2::ProcessDeadStateTransition()
{
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_modelRender.SetScale(m_scale.x, 0.3f, m_scale.z);
	m_charaCon.RemoveRigidBoby();

	ProduceShell();

	for (auto bodyCollision : m_bodyCollisions)
	{
		DeleteGO(bodyCollision);
	}
	if (m_deleteTimer >= m_deleteTime)
	{
		DeleteGO(this);
	}
}

void Enemy2::ProduceShell()
{
	if (m_shell == nullptr)
	{
		m_shell = NewGO<Shell>(0, "shell");
		m_shell->SetPosition(m_position);
	}
}

void Enemy2::ManageState()
{
	switch (m_enemyState)
	{
	case enEnemyState_Idle:
		//待機ステートの遷移処理。
		ProcessIdleStateTransition();
		break;
	case enEnemyState_Chase:

		break;
	case enEnemyState_Dead:
		//死亡ステートの遷移処理。
		ProcessDeadStateTransition();
		break;
	}
}

void Enemy2::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}