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
	/// �e�X�g
	/// </summary>
	void MulScale() override
	{
		m_scale *= 1.2f;
	}

private:

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	//�N���X
	GameOver*					m_gameOver;

	SpawnManager*				m_spawnManager;
	TurretManager*				m_turretManager;

	//���f��
	ModelRender					m_modelRender;

	//UFO
	Vector3						m_position;
	Quaternion					m_rotation;

	//�e�X�g
	Vector3						m_scale;

	//�p�X�ړ�
	std::vector<Vector3>		m_pointList;
	Vector3						m_target;
	int							m_pointNum;
};