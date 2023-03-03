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
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// HP���擾
	/// </summary>
	/// <returns></returns>
	const float& GetDefaultHP() const override
	{
		return m_hp;
	}

	/// <summary>
	/// HP��ݒ�
	/// </summary>
	/// <param name="setHP"></param>
	const void SetDefaultHP(const int setDefaultHP)override
	{
		m_hp = setDefaultHP;
	}

	/// <summary>
	/// �G�l�~�[��HP�����Z����
	/// </summary>
	/// <param name="addHP"></param>
	const void AddEnemyHP(const int value)override
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
	const void SubEnemyHP(const int value)override
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
	/// �S�����Ԃ�ݒ�
	/// </summary>
	/// <param name="bindTime"></param>
	const void SetBind(const float bindTime)override
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
	std::vector<TurretObject*>	m_turrets;
	Vector3						m_difference		= Vector3::Zero;;
	Vector3						m_moveSpeed			= Vector3::Zero;

	//���f��
	Texture						m_emissionMap;
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp				= 0.0f;
	float						m_maxHp				= 0.0f;
	Vector2						m_hpBarPosition		= Vector2::Zero;

	//���
	float						m_bindTimer			= 0.0f;

	//Dempa
	Vector3						m_position			= { 0.0f,0.0f,-8000.0f };
	float 						m_scale				= 0.0f;
	Quaternion					m_rotation			= Quaternion::Identity;
};