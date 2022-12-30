#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

class GameOver;

class SpawnManager;
class TurretManager;

/// <summary>
/// Dempa
/// </summary>
class Dempa : public EnemyObject
{
public:

	Dempa();
	~Dempa();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// ƒ|ƒWƒVƒ‡ƒ“‚ğæ“¾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// HP‚ğæ“¾
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP()override
	{
		return m_hp;
	}

	/// <summary>
	/// HP‚ğİ’è
	/// </summary>
	/// <param name="setHP"></param>
	void SetDefaultHP(const float setDefaultHP)override
	{
		m_hp = setDefaultHP;
	}

	/// <summary>
	/// HP‚ğ‰ÁZ
	/// </summary>
	/// <param name="addHP"></param>
	void AddHP(const float addHP)override
	{
		m_hp += addHP;
	}

	/// <summary>
	/// HP‚ğœZ
	/// </summary>
	/// <param name="addHP"></param>
	void SubHP(const float subHP)override
	{
		m_hp -= subHP;
	}

	/// <summary>
	/// Œ¸‘¬ŠÔ‚ğİ’è
	/// </summary>
	/// <param name="slowTime"></param>
	virtual void SetSlow(const float slowTime)override
	{
		m_slowTimer = slowTime;
	}

	/// <summary>
	/// S‘©ŠÔ‚ğİ’è
	/// </summary>
	/// <param name="bindTime"></param>
	virtual void SetBind(const float bindTime)override
	{
		m_bindTimer = bindTime;
	}

private:

	/// <summary>
	/// UŒ‚‚ğŠÇ—
	/// </summary>
	void Attack();

	/// <summary>
	/// “®ì‚ğŠÇ—
	/// </summary>
	void Move();

	/// <summary>
	/// HP‚ğŠÇ—
	/// </summary>
	void HP();

	//ƒNƒ‰ƒX
	GameOver*					m_gameOver;
	SpawnManager*				m_spawnManager;
	TurretManager*				m_turretManager;

	//UŒ‚ˆ—
	EffectEmitter*				m_dempaAttackEF;
	std::vector<TurretObject*>	m_turrets;

	//ƒ‚ƒfƒ‹
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp = 0.0f;
	float						m_hpMax = 0.0f;
	Vector2						m_hpBarPosition;

	//ó‘Ô
	float						m_slowTimer = 0.0f;
	float						m_bindTimer = 0.0f;

	//Dempa
	Vector3						m_position = { 0.0f,0.0f,-8000.0f };
	Vector3						m_scale;
	Quaternion					m_rotation;

	//ƒpƒXˆÚ“®
	std::vector<Vector3>		m_pointList;
	Vector3						m_target;
	int							m_pointNum = 0;
};