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
	void SetDefaultHP(const int setDefaultHP)override
	{
		m_hp = setDefaultHP;
	}

	/// <summary>
	/// �G�l�~�[��HP�����Z����
	/// </summary>
	/// <param name="addHP"></param>
	void AddEnemyHP(const int value)override
	{
		m_hp += value;
		//�����葝���Ȃ��l��
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0��茸��Ȃ��l��
		else if (m_hp <= 0)
		{
			m_hp = 0;
		}
	}

	/// <summary>
	/// �G�l�~�[��HP�����Z����
	/// </summary>
	/// <param name="addHP"></param>
	void SubEnemyHP(const int value)override
	{
		m_hp -= value;
		//�����葝���Ȃ��l��
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0��茸��Ȃ��l��
		else if (m_hp <= 0)
		{
			m_hp = 0;
		}
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
	virtual void SetBind(const float bindTime)
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
	GameCamera*					m_gameCamera		= nullptr;
	Stage*						m_stage				= nullptr;

	SpawnManager*				m_spawnManager;
	TurretManager*				m_turretManager;

	//���f��
	Texture						m_emissionMap;
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp				= 0.0f;
	float						m_maxHp				= 0.0f;
	Vector2						m_hpBarPosition		= Vector2::Zero;

	//���
	float						m_slowTimer			= 0.0f;
	float						m_bindTimer			= 0.0f;

	//SpaceShip
	Vector3						m_position			= Vector3::Zero;
	Quaternion					m_rotation			= Quaternion::Identity;
	Vector3						m_scale				= Vector3::Zero;

	//�ړ�
	Vector3						m_target			= Vector3::Zero;
};