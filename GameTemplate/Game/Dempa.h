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
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// HP���擾
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP()override
	{
		return m_hp;
	}

	/// <summary>
	/// HP��ݒ�
	/// </summary>
	/// <param name="setHP"></param>
	void SetDefaultHP(const float setDefaultHP)override
	{
		m_hp = setDefaultHP;
	}

	/// <summary>
	/// HP�����Z
	/// </summary>
	/// <param name="addHP"></param>
	void AddHP(const float addHP)override
	{
		m_hp += addHP;
	}

	/// <summary>
	/// HP�����Z
	/// </summary>
	/// <param name="addHP"></param>
	void SubHP(const float subHP)override
	{
		m_hp -= subHP;
	}

	/// <summary>
	/// �������Ԃ�ݒ�
	/// </summary>
	/// <param name="slowTime"></param>
	virtual void SetSlow(const float slowTime)override
	{
		m_slowTimer = slowTime;
	}

	/// <summary>
	/// �S�����Ԃ�ݒ�
	/// </summary>
	/// <param name="bindTime"></param>
	virtual void SetBind(const float bindTime)override
	{
		m_bindTimer = bindTime;
	}

private:

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	/// <summary>
	/// HP���Ǘ�
	/// </summary>
	void HP();

	//�N���X
	GameOver*					m_gameOver			= nullptr;
	SpawnManager*				m_spawnManager		= nullptr;
	TurretManager*				m_turretManager		= nullptr;

	//�U������
	//EffectEmitter*				m_dempaAttackEF;
	std::vector<TurretObject*>	m_turrets;
	Vector3						m_difference		= Vector3::Zero;;
	Vector3						m_moveSpeed			= Vector3::Zero;

	//���f��
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp				= 0.0f;
	float						m_hpMax				= 0.0f;
	Vector2						m_hpBarPosition		= Vector2::Zero;

	//���
	float						m_slowTimer			= 0.0f;
	float						m_bindTimer			= 0.0f;

	//Dempa
	Vector3						m_position			= { 0.0f,0.0f,-8000.0f };
	Vector3						m_scale				= Vector3::Zero;
	Quaternion					m_rotation			= Quaternion::Identity;
};