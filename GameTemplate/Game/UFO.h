#pragma once

#include "EnemyObject.h"

class GameOver;

class SpawnManager;
class TurretManager;

/// <summary>
/// UFO
/// </summary>
class UFO : public EnemyObject
{
public:

	UFO();
	~UFO();
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
	void SetDefaultHP(const float setDefaultHP)override
	{
		m_hp = setDefaultHP;
	}

	/// <summary>
	/// HPを加算
	/// </summary>
	/// <param name="addHP"></param>
	void AddHP(const float addHP)override
	{
		m_hp += addHP;
	}

	/// <summary>
	/// HPを除算
	/// </summary>
	/// <param name="addHP"></param>
	void SubHP(const float subHP)override
	{
		m_hp -= subHP;
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
	GameOver*					m_gameOver;

	SpawnManager*				m_spawnManager;
	TurretManager*				m_turretManager;

	//モデル
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp = 0.0f;
	float						m_hpMax = 0.0f;
	Vector2						m_hpBarPosition;

	//状態
	float						m_bindTimer = 0.0f;

	//UFO
	Vector3						m_position = { 0.0f,0.0f,-8000.0f };
	Quaternion					m_rotation;
	Vector3						m_scale;

	//パス移動
	std::vector<Vector3>		m_pointList;
	Vector3						m_target;
	int							m_pointNum = 0;
};