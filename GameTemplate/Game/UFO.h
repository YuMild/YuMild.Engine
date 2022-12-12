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
	GameOver*					m_gameOver;

	SpawnManager*				m_spawnManager;
	TurretManager*				m_turretManager;

	//���f��
	ModelRender					m_modelRender;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp = 0.0f;
	float						m_hpMax = 0.0f;
	Vector2						m_hpBarPosition;

	//���
	float						m_bindTimer = 0.0f;

	//UFO
	Vector3						m_position = { 0.0f,0.0f,-8000.0f };
	Quaternion					m_rotation;
	Vector3						m_scale;

	//�p�X�ړ�
	std::vector<Vector3>		m_pointList;
	Vector3						m_target;
	int							m_pointNum = 0;
};