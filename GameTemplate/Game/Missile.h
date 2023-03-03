#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

class GameOver;

class SpawnManager;
class TurretManager;

/// <summary>
/// Missile
/// </summary>
class Missile final : public EnemyObject
{
public:

	~Missile();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// HPを取得
	/// </summary>
	/// <returns></returns>
	const float& GetDefaultHP() const override
	{
		return m_hp;
	}

	/// <summary>
	/// HPを設定
	/// </summary>
	/// <param name="setHP"></param>
	const void SetDefaultHP(const int setDefaultHP)override
	{
		m_hp = setDefaultHP;
	}

	/// <summary>
	/// エネミーのHPを加算する
	/// </summary>
	/// <param name="addHP"></param>
	const void AddEnemyHP(const int value)override
	{
		m_hp += value;
		//上限より増えない様に
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0より減らない様に
		else if (m_hp <= 0)
		{
			m_hp = 0;
		}
	}

	/// <summary>
	/// エネミーのHPを除算する
	/// </summary>
	/// <param name="addHP"></param>
	const void SubEnemyHP(const int value)override
	{
		m_hp -= value;
		//上限より増えない様に
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0より減らない様に
		else if (m_hp <= 0)
		{
			m_hp = 0;
		}
	}

	/// <summary>
	/// 拘束時間を設定
	/// </summary>
	/// <param name="bindTime"></param>
	const void SetBind(const float bindTime)override
	{
		m_bindTimer = bindTime;
	}

private:

	/// <summary>
	/// 動作を管理
	/// </summary>
	void Move();

	/// <summary>
	/// HPを管理
	/// </summary>
	void HP();

	//クラス
	GameOver*					m_gameOver			= nullptr;
	SpawnManager*				m_spawnManager		= nullptr;
	TurretManager*				m_turretManager		= nullptr;

	//攻撃処理
	std::vector<TurretObject*>	m_turrets;
	Vector3						m_difference		= Vector3::Zero;;
	Vector3						m_moveSpeed			= Vector3::Zero;

	//モデル
	Texture						m_emissionMap;
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp				= 0.0f;
	float						m_maxHp				= 0.0f;
	Vector2						m_hpBarPosition		= Vector2::Zero;

	//状態
	float						m_bindTimer			= 0.0f;

	//Dempa
	Vector3						m_position			= { 0.0f,0.0f,-8000.0f };
	float 						m_scale				= 0.0f;
	Quaternion					m_rotation			= Quaternion::Identity;
};