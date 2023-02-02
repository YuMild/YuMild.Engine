#pragma once

#include "EnemyObject.h"

class GameOver;
class GameCamera;
class Stage;

class SpawnManager;
class TurretManager;

/// <summary>
/// SpaceShip
/// </summary>
class SpaceShip : public EnemyObject
{
public:

	~SpaceShip();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// HPを取得
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP()override
	{
		return m_hp;
	}

	/// <summary>
	/// HPを設定
	/// </summary>
	/// <param name="setHP"></param>
	void SetDefaultHP(const int setDefaultHP)override
	{
		m_hp = setDefaultHP;
	}

	/// <summary>
	/// エネミーのHPを加算する
	/// </summary>
	/// <param name="addHP"></param>
	void AddEnemyHP(const int value)override
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
	void SubEnemyHP(const int value)override
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
	/// 減速時間を設定
	/// </summary>
	/// <param name="slowTime"></param>
	virtual void SetSlow(const float slowTime)override
	{
		m_slowTimer = slowTime;
	}

	/// <summary>
	/// 拘束時間を設定
	/// </summary>
	/// <param name="bindTime"></param>
	virtual void SetBind(const float bindTime)
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
	GameCamera*					m_gameCamera		= nullptr;
	Stage*						m_stage				= nullptr;

	SpawnManager*				m_spawnManager;
	TurretManager*				m_turretManager;

	//モデル
	Texture						m_emissionMap;
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp				= 0.0f;
	float						m_maxHp				= 0.0f;
	Vector2						m_hpBarPosition		= Vector2::Zero;

	//状態
	float						m_slowTimer			= 0.0f;
	float						m_bindTimer			= 0.0f;

	//SpaceShip
	Vector3						m_position			= Vector3::Zero;
	Quaternion					m_rotation			= Quaternion::Identity;
	Vector3						m_scale				= Vector3::Zero;

	//移動
	Vector3						m_target			= Vector3::Zero;
};